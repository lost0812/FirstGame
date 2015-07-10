#include "GameHeroBullet.h"


GameHeroBullet * GameHeroBullet::create()
{
	GameHeroBullet *bullet = new (std::nothrow) GameHeroBullet();
	if( bullet && bullet->init())
	{
		bullet->autorelease();
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

GameHeroBullet::GameHeroBullet(void)
{
}


GameHeroBullet::~GameHeroBullet(void)
{
}

void GameHeroBullet::SetVisible()
{
	m_is_visible = true;
	setVisible( true );
}

void GameHeroBullet::SetNotVisible()
{
	m_is_visible = false;
	setVisible( false );
}

bool GameHeroBullet::GetVisible()
{
	return isVisible();
}

bool GameHeroBullet::init()
{
	Sprite::init();

	setContentSize( Size(21,52) );

	Sprite *body = Sprite::create("HeroZD.png");
//	body->runAction( CCRepeatForever::create( CCRotateBy::create( 1, 360 ) ) );
	addChild( body );

	return true;
}
