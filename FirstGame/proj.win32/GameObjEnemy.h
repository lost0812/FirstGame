#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class GameObjEnemy : public Sprite
{
public:
	static GameObjEnemy* create();
public:
	GameObjEnemy(void);
	~GameObjEnemy(void);

public:
	virtual bool init();

public:
	void ReleaseBullet( float time );
	void Die();
	void ReStart();
	void MoveStart();

private:
	Sprite *m_body;
	Sprite *m_boom;

	bool m_is_life;

	int m_move_type;
};

