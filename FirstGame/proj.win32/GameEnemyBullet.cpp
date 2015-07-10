#include "GameEnemyBullet.h"


GameEnemyBullet * GameEnemyBullet::create()
{
	GameEnemyBullet *bullet = new (std::nothrow) GameEnemyBullet();
	if( bullet && bullet->init())
	{
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

GameEnemyBullet::GameEnemyBullet(void)
{
}


GameEnemyBullet::~GameEnemyBullet(void)
{
}

void GameEnemyBullet::SetVisible()
{
	setVisible( true );
	m_is_visible = true;
}

void GameEnemyBullet::SetNotVisible()
{
	setVisible( false );
	m_is_visible = false;
}

bool GameEnemyBullet::GetVisible()
{
	return isVisible();
}

bool GameEnemyBullet::init()
{
	Sprite::init();

	setContentSize( Size(21,52) );

	Sprite *body = Sprite::create("DrDogZD.png");
	body->runAction( CCRepeatForever::create( CCRotateBy::create( 1, 360 ) ) );
	addChild( body );

	return true;
}