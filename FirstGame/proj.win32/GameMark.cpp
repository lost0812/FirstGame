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

	for( int i = 4; i >= 0; i-- )
	{
		m_array_score.at(i)->setTextureRect( Rect( 4+11*(temp_score%10), 0, 15, 30 ) );
		temp_score /= 10;
	}
}

void GameMark::GetRect(Rect &rect)
{
	Point position = getPosition();
	Point anchor = getAnchorPoint();
	Size size = getContentSize();
	rect = Rect( position.x-size.width*anchor.x, position.y-size.height*anchor.y, size.width, size.height );
}

bool GameMark::init()
{
	Sprite::init();

	//Size size = Director::sharedDirector()->getWinSize();
	setContentSize( Size( 110, 30 ) );

	Sprite *title = Sprite::create( "score.png" );
	title->setPosition( -27.5, 0 );
	addChild( title );


	Sprite *number;
	for( int i = 0; i < 5; i++ )
	{
		number = Sprite::create( "shu.png" ); 
		number->setTextureRect( CCRectMake( 4, 0, 11, 30) );
		number->setPosition( i * 11, 0 );

		m_array_score.pushBack( number );
		addChild( number );
	} 
	m_score = 0;

	return true;
}

void GameMark::addChild(Node *child)
{
	Size adjust_point = getContentSize();
	Point old_point = child->getPosition();

	child->setPosition( old_point.x + adjust_point.width/2, old_point.y + adjust_point.height/2 );
	Node::addChild( child );
}





