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
	CCRect Rect();
public:
	virtual void OnEnter();
	virtual void OnExit();
	virtual bool init( void );

public:
	bool ContainsTouchLocation( Touch *touch );

	virtual bool onTouchBegan( Touch *touch, Event *event );
	virtual void onTouchMoved( Touch *touch, Event *event );
	virtual void onTouchEnded( Touch *touch, Event *event );

	virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();

private:
	CCSprite *m_left_hand;
	CCSprite *m_right_hand;
	CCPoint m_offset_point;
	bool m_is_control;
};

