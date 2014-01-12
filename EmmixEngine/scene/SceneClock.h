#pragma once

// GL
#include <GLFW\glfw3.h>

/*
SceneClock provides the ability to measure and control simulated time within a scene
*/
class SceneClock
{
public:
	SceneClock(void);
	~SceneClock(void);

public:
	void startClock( void );
	void stopClock( void );
	const double & getDeltaTime( void );

private:
	double _frameStartTime;
	double _deltaTime;
};

