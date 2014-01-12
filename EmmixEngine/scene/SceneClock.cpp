#include "SceneClock.h"


SceneClock::SceneClock( void )
	:	_frameStartTime	( 0 ),
		_deltaTime		( 0 )
{
}


SceneClock::~SceneClock(void)
{
}



/*
Start the clock timer. Needs to be followed by a class to stopClock at some point
*/
void SceneClock::startClock( void )
{
	_frameStartTime = glfwGetTime();
}



/*
Stop the clock timer. Updates _deltaTime to indicate the amount of time elapsed since the call to startClock
*/
void SceneClock::stopClock( void )
{
	double frameEndTime = glfwGetTime();
	_deltaTime = frameEndTime - _frameStartTime;
}



// Accessors

const double & SceneClock::getDeltaTime( void ) { return _deltaTime; }