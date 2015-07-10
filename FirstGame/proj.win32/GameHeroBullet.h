#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class GameHeroBullet : public Sprite
{
public:
	static GameHeroBullet *create();
public:
	GameHeroBullet(void);
	~GameHeroBullet(void);
public:
	void SetVisible();
	void SetNotVisible();
	bool GetVisible();

public:
	virtual bool init();

private:
	bool m_is_visible;
};

