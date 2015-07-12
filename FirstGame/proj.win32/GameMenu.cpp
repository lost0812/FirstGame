#include "GameMenu.h"
#include "GameMain.h"


GameMenu * GameMenu::create()
{
	GameMenu *menu = new (std::nothrow) GameMenu();
	if( menu && menu->init())
	{
		menu->autorelease();
		return menu;
	}
	CC_SAFE_DELETE(menu);
	return nullptr;
}



Scene * GameMenu::CreateScene()
{
	Scene *scene = Scene::create();
	scene->addChild( GameMenu::create() );
	return scene;
}

GameMenu::GameMenu(void)
{
}


GameMenu::~GameMenu(void)
{
}

void GameMenu::GameStart( Ref *ref )
{
	Director::sharedDirector()->setDepthTest(true);
	Director::sharedDirector()->replaceScene( TransitionPageTurn::create(1.0f, GameMain::CreateScene(),true));
}

void GameMenu::GameAbout(Ref *ref)
{

}

bool GameMenu::init()
{
	Layer::init();

	Size size = Director::sharedDirector()->getWinSize();

	//��ʼ������
	Sprite *bg = Sprite::create( "menu-bg.png" );
	bg->setPosition( size.width/2, size.height/2);
	addChild( bg );

	//��ʼ������
	Sprite *title = Sprite::create( "menu-title.png" );
	title->setPosition( size.width/2, size.height - title->getContentSize().height );
	addChild( title );

	//��ʼ����ť
	MenuItemImage *game_item = MenuItemImage::create( "menu-game.png", "menu-game2.png", this, menu_selector( GameMenu::GameStart ) );
	//game_item->setPositionY( 100 );
	game_item->setEnabled( true );

	MenuItemImage *about_item = MenuItemImage::create( "menu-about.png", "menu-about2.png", this, menu_selector( GameMenu::GameAbout ) );
	about_item->setPositionY( -50 );
	about_item->setEnabled( true );

	//��ʼ���˵�
	m_menu = Menu::create( game_item, about_item, NULL );
	addChild( m_menu );
	return true;
};
