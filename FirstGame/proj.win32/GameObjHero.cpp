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

cocos2d::CCRect GameObjHero::Rect()
{
	return CCRect();
}

void GameObjHero::OnEnter()
{
	Sprite::onEnter();

}

void GameObjHero::OnExit()
{

}

bool GameObjHero::init()
{
	Sprite::init();

	setContentSize( CCSizeMake(85,90));
	//CCDirector::sharedDirector()->getTouchDispatcher()->addT

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

	schedule( schedule_selector( GameObjHero::ReleaseBullet ), 1.0f );





	return true;
}

bool GameObjHero::ContainsTouchLocation(Touch *touch)
{
	return true;
}

bool GameObjHero::onTouchBegan(Touch *touch, Event *event)
{
	return true;
}

void GameObjHero::onTouchMoved(Touch *touch, Event *event)
{

}

void GameObjHero::onTouchEnded(Touch *touch, Event *event)
{

}

void GameObjHero::touchDelegateRetain()
{

}

void GameObjHero::touchDelegateRelease()
{

}
