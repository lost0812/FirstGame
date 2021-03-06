#include "GameObjHero.h"


GameObjHero * GameObjHero::create()
{
	GameObjHero *hero = new (std::nothrow) GameObjHero();
	if (hero && hero->init())
	{
		hero->autorelease();
		return hero;
	}
	CC_SAFE_DELETE(hero);
	return nullptr;
}

GameObjHero::GameObjHero(void)
{
}


GameObjHero::~GameObjHero(void)
{
}

void GameObjHero::ReleaseBullet(float time)
{

}

void GameObjHero::GetRect( Rect &rect )
{
	Point position = getPosition();
	Point anchor = getAnchorPoint();
	Size size = getContentSize();
	rect = Rect( position.x-size.width*anchor.x, position.y-size.height*anchor.y, size.width, size.height );
}

bool GameObjHero::init()
{
	Sprite::init();

	setContentSize( CCSizeMake(85,90));

	//事件监听
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2( GameObjHero::onTouchBegan, this );
	listener->onTouchMoved = CC_CALLBACK_2( GameObjHero::onTouchMoved, this );
	listener->onTouchEnded = CC_CALLBACK_2( GameObjHero::onTouchEnded, this );

	listener->setSwallowTouches( false );

	auto dispatcher = Director::getInstance()->getEventDispatcher();

	dispatcher->addEventListenerWithSceneGraphPriority( listener, this );

	//主体

	//身体
	CCSprite *mainSprite = CCSprite::create( "catBody1.png" );

	//身体动作
	CCAnimation *animation = CCAnimation::create();

	animation->addSpriteFrameWithFileName( "catBody1.png" );
	animation->addSpriteFrameWithFileName( "catBody2-4.png" );
	animation->addSpriteFrameWithFileName( "catBody3.png" );
	animation->addSpriteFrameWithFileName( "catBody2-4.png" );

	animation->setDelayPerUnit(0.1f);//每帧时间间隔
	animation->setRestoreOriginalFrame( true );

	mainSprite->runAction( CCRepeatForever::create( CCAnimate::create( animation ) ) );

	//载入身体
	addChild( mainSprite );

	//尾巴
	CCSprite *tailSprite = CCSprite::create( "catTail.png" );

	tailSprite->setAnchorPoint( ccp( 0.5, 1 ) );
	tailSprite->setPosition( ccp( -5, -29 ) );
	tailSprite->setScale( 0.5 );
	tailSprite->setRotation( 20 );

	auto action = CCSequence::create( CCRotateBy::create( 0.5, -40 ), CCRotateBy::create( 0.5, 40 ), NULL );
	tailSprite->runAction( CCRepeatForever::create( action ) );

	addChild( tailSprite );

	//手
	m_left_hand = CCSprite::create( "catHand1.png" );
	m_left_hand->setAnchorPoint( ccp( 1, 0.5 ) );
	m_left_hand->setPosition( ccp( -18, -20 ) );
	addChild( m_left_hand );

	m_right_hand = CCSprite::create( "catHand2.png" );
	m_right_hand->setAnchorPoint( ccp( 0, 0.5 ) );
	m_right_hand->setPosition( ccp( 18, -20 ) );
	addChild( m_right_hand );

	m_offset_point = ccp( 0, 0 );

	m_is_control = false;

	return true;
}

void GameObjHero::addChild(Node *child)
{
	Size adjust_point = getContentSize();
	Point old_point = child->getPosition();

	child->setPosition( old_point.x + adjust_point.width/2, old_point.y + adjust_point.height/2 );
	Node::addChild( child );
}

bool GameObjHero::ContainsTouchLocation(Touch *touch)
{
	Point touchPoint = touch->getLocation();

	Rect rect;
	GetRect( rect );

	return rect.containsPoint( touchPoint );
}

bool GameObjHero::onTouchBegan(Touch *touch, Event *event)
{
	if( ContainsTouchLocation( touch ) )
	{
		m_is_control = true;
		Point touchPoint = touch->getLocation();
		Point heroPoint = getPosition();
		m_offset_point.x = heroPoint.x - touchPoint.x;
		m_offset_point.y = heroPoint.y - touchPoint.y;
		return true;
	}
	return false;
}

void GameObjHero::onTouchMoved(Touch *touch, Event *event)
{
	if( m_is_control )
	{
		Point touchPoint = touch->getLocation();

		Point newHeroPoint;
		newHeroPoint.x = m_offset_point.x + touchPoint.x;
		newHeroPoint.y = m_offset_point.y + touchPoint.y;
		
		if( newHeroPoint.x < getPosition().x )
		{
			m_left_hand->setFlippedY( true );
			m_right_hand->setFlippedY( false );
		}
		else 
		{
			m_left_hand->setFlippedY( false );
			m_right_hand->setFlippedY( true );
		}

		setPosition( newHeroPoint );
	}
}

void GameObjHero::onTouchEnded(Touch *touch, Event *event)
{
	if( m_is_control )
	{
		m_is_control = false;
	}

	m_left_hand->setFlippedY( false );
	m_right_hand->setFlippedY( false );
}
