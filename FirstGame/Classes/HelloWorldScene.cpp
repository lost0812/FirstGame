#include "HelloWorldScene.h"
#include "proj.win32/GameObjHero.h"
#include "proj.win32/GameObjEnemy.h"
#include "proj.win32/GameHeroBullet.h"
#include "proj.win32/GameEnemyBullet.h"
#include "proj.win32/GameMark.h"
#include "proj.win32/GameMain.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
   this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
	/*
	auto hero = GameObjHero::create();
	
	hero->setPosition( Vec2( visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ) );
	hero->runAction( MoveBy::create( 0.5, ccp( 0, 150 ) ) );

	addChild( hero, 0 );

	auto enemy = GameObjEnemy::create();

	enemy->setPosition( Vec2( visibleSize.width/2 + origin.x, visibleSize.height*3/4 + origin.y ) );
	enemy->MoveStart();

	addChild( enemy );

	auto heroBullet = GameHeroBullet::create();
	heroBullet->setPosition( 100, 100 );
	addChild( heroBullet );

	auto enemyBullet = GameEnemyBullet::create();
	enemyBullet->setPosition( 200, 100 );
	addChild( enemyBullet );

	auto mark = GameMark::create();
	mark->setPosition( origin.x + mark->getContentSize().width/2 , visibleSize.height );
	mark->AddNumber( 1230 );
	addChild( mark );*/

	auto gameMain = GameMain::create();
	addChild( gameMain );

    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
