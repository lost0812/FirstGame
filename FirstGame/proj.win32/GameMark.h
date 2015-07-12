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
	void GetRect( Rect &rect );

public:
	virtual bool init();
	virtual void addChild( Node *child );

private:
	int m_score;
	Vector<Sprite *> m_array_score;
};

