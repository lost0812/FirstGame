#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class GameObjHero : public Sprite
{
public:
	static GameObjHero *create(); 
public:
	GameObjHero(void);
	~GameObjHero(void);
public:
	void ReleaseBullet( float time );
	void GetRect( Rect &rect );
public:
	virtual bool init( void );
	virtual void OnEnter();
	virtual void OnExit();

public:
	bool ContainsTouchLocation( Touch *touch );

	virtual bool onTouchBegan( Touch *touch, Event *event );
	virtual void onTouchMoved( Touch *touch, Event *event );
	virtual void onTouchEnded( Touch *touch, Event *event );

	virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();

private:
	Sprite *m_left_hand;
	Sprite *m_right_hand;
	Point m_offset_point;
	bool m_is_control;
};

