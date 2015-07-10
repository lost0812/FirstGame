#include "GameMark.h"


GameMark * GameMark::create()
{
	GameMark *mark = new (std::nothrow) GameMark();
	if( mark && mark->init())
	{
		mark->autorelease();
		return mark;
	}
	CC_SAFE_DELETE(mark);
	return nullptr;
}

GameMark::GameMark(void)
{
}


GameMark::~GameMark(void)
{
}

void GameMark::AddNumber(int score)
{
	m_score += score;
	if( m_score >= 100000 )
		m_score = 99999;

	int temp_score = m_score;

	for( int i = 0; i < 5; i++ )
	{
		((Sprite *)(m_array_score->objectAtIndex(i)))->setTextureRect( Rect( 4+15*(temp_score%10), 0, 15, 30 ) );
		temp_score /= 10;
	}
}

bool GameMark::init()
{
	Sprite::init();

	//Size size = Director::sharedDirector()->getWinSize();
	setContentSize( Size( 105, 30 ) );

	Sprite *title = Sprite::create( "score.png" );
	int width = title->getContentSize().width;
	setPosition( title->getContentSize().width/2,0 );
	addChild( title );


	m_array_score = Array::create();
	Sprite *number;
	for( int i = 0; i < 5; i++ )
	{
		number = Sprite::create( "shu.png" ); 
		number->setTextureRect( CCRectMake( 4, 0, 12, 30) );
		number->setPosition( 55 + 6 + i * 12, 0 );

		m_array_score->addObject( number );
		addChild( number );
	} 
	m_score = 0;

	return true;
}






