#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class GameMark : public Sprite
{
public:
	static GameMark *create();

public:
	GameMark(void);
	~GameMark(void);
public:
	void AddNumber( int score );

public:
	virtual bool init();

private:
	int m_score;
	Array *m_array_score;
};

