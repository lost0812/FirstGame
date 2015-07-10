#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class GameEnemyBullet : public Sprite
{
public:
	static GameEnemyBullet *create();
public:
	GameEnemyBullet(void);
	~GameEnemyBullet(void);
public:
	void SetVisible();
	void SetNotVisible();
	bool GetVisible();

public:
	virtual bool init();

private:
	bool m_is_visible;
};

