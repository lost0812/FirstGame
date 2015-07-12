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

void GameHeroBullet::GetRect(Rect &rect)
{
	Point position = getPosition();
	Point anchor = getAnchorPoint();
	Size size = getContentSize();
	rect = Rect( position.x-size.width*anchor.x, position.y-size.height*anchor.y, size.width, size.height );
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

void GameHeroBullet::addChild(Node *child)
{
	Size adjust_point = getContentSize();
	Point old_point = child->getPosition();

	child->setPosition( old_point.x + adjust_point.width/2, old_point.y + adjust_point.height/2 );
	Node::addChild( child );
}
