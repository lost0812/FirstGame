#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class GameMenu : public Layer
{
public:
	static GameMenu *create();
	static Scene *CreateScene();
public:
	GameMenu(void);
	~GameMenu(void);
public:
	void GameStart( Ref *ref );
	void GameAbout( Ref *ref );

public:
	virtual bool init();

private:
	Menu *m_menu;
};

