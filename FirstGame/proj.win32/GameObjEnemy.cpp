#include "GameObjEnemy.h"


GameObjEnemy* GameObjEnemy::create()
{
	GameObjEnemy *enemy = new (std::nothrow) GameObjEnemy();
	if( enemy && enemy->init())
	{
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}

GameObjEnemy::GameObjEnemy(void)
{
}


GameObjEnemy::~GameObjEnemy(void)
{
}

bool GameObjEnemy::init()
{
	Sprite::init();

	setContentSize( CCSizeMake( 99, 111 ) );

	//身体
	m_body = Sprite::create( "DrDog1.png" );
	
	//身体动作
	Animation *animation = Animation::create();

	animation->addSpriteFrameWithFileName( "DrDog1.png" );
	animation->addSpriteFrameWithFileName( "DrDog2.png" );

	animation->setDelayPerUnit( 0.1f );
	animation->setRestoreOriginalFrame( true );

	m_body->runAction( RepeatForever::create( Animate::create( animation ) ) );

	addChild( m_body );

	//爆炸效果
	m_boom = Sprite::create( "boom1.png" );
	addChild( m_boom );

	m_boom->setVisible( false );

	//存活
	m_is_life = true;

	return true;
}

void GameObjEnemy::addChild(Node *child)
{
	Size adjust_point = getContentSize();
	Point old_point = child->getPosition();

	child->setPosition( old_point.x + adjust_point.width/2, old_point.y + adjust_point.height/2 );
	Node::addChild( child );
}

void GameObjEnemy::Die()
{
	m_is_life = false;

	m_body->setVisible( false );
	m_boom->setVisible( true );

	stopAllActions();

	//爆炸动画
	Animation *boomAnimation = Animation::create();

	boomAnimation->addSpriteFrameWithFileName("boom1.png");
	boomAnimation->addSpriteFrameWithFileName("boom2.png");
	boomAnimation->addSpriteFrameWithFileName("boom3.png");
	boomAnimation->addSpriteFrameWithFileName("boom4.png");
	boomAnimation->addSpriteFrameWithFileName("boom5.png");

	boomAnimation->setDelayPerUnit( 0.1f );
	boomAnimation->setRestoreOriginalFrame( true );

	m_boom->runAction( 
		Sequence::create( 
			Animate::create( boomAnimation ), 
			CallFunc::create( this, callfunc_selector( GameObjEnemy::ReStart ) ), 
			NULL ));
}

void GameObjEnemy::SetDie()
{
	m_is_life = false;
	Die();
}

void GameObjEnemy::ReStart()
{
	m_is_life = true;

	m_body->setVisible( true );
	m_boom->setVisible( false );
	
	MoveStart();
}


void GameObjEnemy::MoveStart()
{
	m_is_life = true;

	int type = 0;//CCRANDOM_0_1() * 3;

	//ccBezierConfig bezier1;
	//bezier1.controlPoint_1 = Vec2( 400, 330 );
	//bezier1.controlPoint_2 = Vec2( -400, -330 );
	//bezier1.endPosition = Vec2( getPosition().x + 200, getPosition().y );

	//CCBezierTo *bezierTo1 = CCBezierTo::create( 6, bezier1 );
	//

	//ccBezierConfig bezier2;
	//bezier2.controlPoint_1 = Vec2( -400, 330 );
	//bezier2.controlPoint_2 = Vec2( 400, -330 );
	//bezier2.endPosition = Vec2( getPosition().x - 200, getPosition().y  );

	//CCBezierTo *bezierTo2 = CCBezierTo::create( 6, bezier2 ); 


	switch( type )
	{
	case 0:
		runAction( 
			RepeatForever::create(
				CCSequence::create(  
					CCMoveBy::create( 6, Vec2( 200, 0 ) ),
					CCMoveBy::create( 6, Vec2( -400, 0 ) ),
					CCMoveBy::create( 6, Vec2( 200, 0 ) ),
					NULL )));
		break;
	//case 1:
	//	runAction( CCSequence::create(  bezierTo1,
	//									CCCallFunc::create( this, callfunc_selector( GameObjEnemy::MoveStart ) ), NULL ));
	//	break;
	//case 2:
	//	runAction( CCSequence::create(  bezierTo2,
	//									CCCallFunc::create( this, callfunc_selector( GameObjEnemy::MoveStart ) ), NULL ));
		break;
	}

}

bool GameObjEnemy::IsLife()
{
	return m_is_life;
}

void GameObjEnemy::SetLife(bool life)
{
	m_is_life = life;
}

void GameObjEnemy::GetRect(Rect &rect)
{
	Point position = getPosition();
	Point anchor = getAnchorPoint();
	Size size = getContentSize();
	rect = Rect( position.x-size.width*anchor.x, position.y-size.height*anchor.y, size.width, size.height );
}
