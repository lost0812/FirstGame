#include "GameMain.h"



GameMain * GameMain::create()
{
	GameMain *main = new (std::nothrow) GameMain();
	if( main && main->init())
	{
		main->autorelease();
		return main;
	}
	CC_SAFE_DELETE(main);
	return nullptr;

}

GameMain::GameMain(void)
{
}


GameMain::~GameMain(void)
{
}

bool GameMain::init()
{
	Layer::init();

	Size size = getContentSize();

	//背景

 	m_background = Sprite::create("bg.png");
	m_background->setPosition( Vec2( m_background->getContentSize().width/2, m_background->getContentSize().height/2 ) );
 	addChild( m_background );
	
	//创建主角
	m_hero = GameObjHero::create();
	m_hero->setPosition( Vec2( size.width/2, -m_hero->getContentSize().height ) );
	addChild( m_hero );
	m_hero->runAction( MoveBy::create( 1, Vec2( 0, m_hero->getContentSize().height*3 ) ) );

	//创建敌人
	for( int i = 0; i < 3; i++ )
	{
		GameObjEnemy *enemy = GameObjEnemy::create();
		enemy->setPosition( size.width/4 * ( i + 1 ) + enemy->getContentSize().width / 2, size.height - enemy->getContentSize().height );
		enemy->MoveStart();
		m_enemies.pushBack( enemy );
		addChild( enemy );
	}
	m_enemies.at(0)->Die();


	//创建血条
	for( int i = 0; i < 3; i++ )
	{
		Sprite *blood = Sprite::create("cat.png");
		blood->setPosition( Vec2( 35+i*35, size.height - 30 ) );
		m_bloods.pushBack( blood );
		addChild( blood );
	}
	m_blood = 3;

	//创建分数
	m_score = GameMark::create();
	m_score->setPosition( size.width - m_score->getContentSize().width/2 - 20, size.height - m_score->getContentSize().height/2 - 10 );
	addChild( m_score );

	//创建结束画面
	m_game_over = Sprite::create( "gameover.png" );
	m_game_over->setPosition( size.width/2, size.height/2 );
	m_game_over->setVisible( false );
	addChild( m_game_over );

	//创建菜单
	MenuItemImage *close_item = MenuItemImage::create("menuItem1.png", "menuItem2.png", this, menu_selector(GameMain::menuBackCallBack) );
	close_item->setPosition( size.width/2, size.height/2 );
	
	m_menu = Menu::create( close_item, NULL );
	m_menu->setPosition( Point::ZERO );
	m_menu->setVisible( false );
	m_menu->setEnabled( false );
	addChild( m_menu );

	//其他
	m_is_reduce = false;
	m_is_over = false;
	

	scheduleUpdate();
	schedule( schedule_selector( GameMain::HeroSendBullet ), 0.5f );
	schedule( schedule_selector( GameMain::EnemySendBullet ), 1.0f );
	return true;
}

void GameMain::update(float delta)
{
	//背景移动
	Vec2 background_point = m_background->getPosition();
	if( background_point.y >= 2 )
	{
		m_background->setPosition( background_point.x, background_point.y - 2 );
	}
	else
	{
		m_background->setPosition( background_point.x, m_background->getContentSize().height/2 );
	}

	//碰撞检测
	Point hero_point = m_hero->getPosition();


	Rect rect1;
	Rect rect2;
	//敌人的碰撞检测
	for( int i = 0; i < m_enemies.size();i++ )
	{
		GameObjEnemy *enemy = m_enemies.at(i);
		if( enemy->IsLife() )
		{
			enemy->GetRect( rect1 );
			//和子弹的碰撞检测
			for( int j = 0; j < m_hero_bullets.size(); j++ )
			{
				m_hero_bullets.at(j)->GetRect(rect2);
				if( IsCollion(rect1,rect2) )
				{
					enemy->SetDie();
					m_score->AddNumber( 200 );
					break;
				}
			}

			//和主角的碰撞检测
			m_hero->GetRect( rect2 );
			if( !m_is_reduce )
			{
				if( IsCollion( rect1, rect2 ) )
				{
					SetHeroHurt();
				}
			}
		}
	}
	if( !m_is_over && !m_is_reduce )
	{
		m_hero->GetRect( rect1 );
		for( int j = 0; j < m_enemy_bullets.size(); j++ )
		{
			m_enemy_bullets.at(j)->GetRect(rect2);
			if( IsCollion(rect1,rect2) )
			{
				SetHeroHurt();
				break;
			}
		}
	}
}

void GameMain::menuBackCallBack(Ref *ref)
{

}

bool GameMain::IsCollion(Rect &rect1, Rect &rect2)
{
	if( ( rect1.origin.x >= rect2.origin.x && rect1.origin.x <= rect2.origin.x + rect2.size.width )
	 || ( rect1.origin.x <= rect2.origin.x && rect1.origin.x + rect1.size.width >= rect2.origin.x ) )
	{
		if( ( rect1.origin.y >= rect2.origin.y && rect1.origin.y <= rect2.origin.y + rect2.size.height )
		 || ( rect1.origin.y <= rect2.origin.y && rect1.origin.y + rect1.size.height >= rect2.origin.y ) )
		{
			return true;
		}
	}
	return false;
}

void GameMain::SetHeroHurt()
{
	m_hero->stopAllActions();

	m_blood--;
	if( m_blood >= 0 )
	{
		(m_bloods.at( m_blood ))->setVisible( false );
	}
	else
	{
		m_is_over = true;
		SetOver();
	}

	ActionInterval *action = Blink::create( 5, 10 );
	m_hero->runAction( action );

	m_is_reduce = true;
	schedule(schedule_selector( GameMain::ReSetReduce ), 5 );
}

void GameMain::SetOver()
{
	stopAllActions();
	m_menu->setVisible( true );
	m_menu->setEnabled( true );
}

void GameMain::ReSetReduce( float time )
{
	m_is_reduce = false;
}

void GameMain::HeroSendBullet(float time)
{
	if( !m_is_over )
	{
		GameHeroBullet *hero_bullet = GameHeroBullet::create();
		Point position = m_hero->getPosition();
		hero_bullet->setPosition( position );
		hero_bullet->runAction( Sequence::create(   MoveBy::create( 3.0f, Vec2( 0, 480 ) ), 
													CallFuncN::create( this, callfuncN_selector( GameMain::HeroReleseBullet ) ), 
													NULL ) );

		m_hero_bullets.pushBack( hero_bullet );
		addChild( hero_bullet );
	}
}

void GameMain::EnemySendBullet(float time)
{
	for( int i = 0; i < 3; i++ )
	{
		GameObjEnemy *enemy = m_enemies.at(i);

		if( enemy->IsLife() )
		{
			Point position = enemy->getPosition();
			float director = rand_0_1() - 0.5;

			GameEnemyBullet *enemy_bullet = GameEnemyBullet::create();
			enemy_bullet->setPosition( position );
			enemy_bullet->runAction( Sequence::create(  MoveBy::create( 6.0f, Vec2( director * 2000, - 480 ) ),
														CallFuncN::create( this, callfuncN_selector( GameMain::EnemyReleseBullet ) ),
														NULL ) );
			m_enemy_bullets.pushBack( enemy_bullet );
			addChild( enemy_bullet );
		}
	}
	GameHeroBullet *hero_bullet = GameHeroBullet::create();
	Point position = m_hero->getPosition();
	hero_bullet->setPosition( position );
	hero_bullet->runAction( Sequence::create(   MoveBy::create( 3.0f, Vec2( 0, 480 ) ), 
		CallFuncN::create( this, callfuncN_selector( GameMain::HeroReleseBullet ) ), 
		NULL ) );

	m_hero_bullets.pushBack( hero_bullet );
	addChild( hero_bullet );
}

void GameMain::HeroReleseBullet(Node * node)
{
	for( int i = 0; i < m_hero_bullets.size(); i++ )
	{
		if( m_hero_bullets.at( i ) == node )
		{
			m_hero_bullets.at(i)->SetNotVisible();
			m_hero_bullets.erase( i );
		}
	}
}

void GameMain::EnemyReleseBullet(Node *node)
{	
	for( int i = 0; i < m_enemy_bullets.size(); i++ )
	{
		if( m_enemy_bullets.at( i ) == node )
		{
			m_enemy_bullets.at(i)->SetNotVisible();
			m_enemy_bullets.erase( i );
		}
	}
}
