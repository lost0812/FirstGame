#pragma once

#include "cocos2d.h"

#include "GameObjHero.h"
#include "GameObjEnemy.h"
#include "GameHeroBullet.h"
#include "GameEnemyBullet.h"
#include "GameMark.h"

using namespace cocos2d;

class GameMain : public Layer
{
public:
	static GameMain *create();
	static Scene *CreateScene( );
public:
	GameMain(void);
	~GameMain(void);

public:
	virtual bool init();
	virtual void update( float delta );

public:
	void menuBackCallBack( Ref *ref );
	bool IsCollion( Rect &rect1, Rect &rect2 );
	void SetHeroHurt();
	void SetOver();
	void ReSetReduce( float time );
	void HeroSendBullet( float time );
	void EnemySendBullet( float time );
	void HeroReleseBullet( Node *node );
	void EnemyReleseBullet( Node *node );
private:
	Sprite *m_background;
	GameObjHero *m_hero;
	Vector< GameObjEnemy * > m_enemies;

	Vector< GameHeroBullet * > m_hero_bullets;
	Vector< GameEnemyBullet * > m_enemy_bullets;

	Vector< Sprite * > m_bloods;
	int m_blood;

	GameMark *m_score;

	Sprite *m_game_over;
	Menu *m_menu;

	bool m_is_reduce;
	bool m_is_over;
};

