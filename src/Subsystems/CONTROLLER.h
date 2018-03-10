#ifndef CONTROLLER_h
#define CONTROLLER_h

#include <Arduino.h>

class ROBOT;

class CONTROLLER
{
public:
	CONTROLLER(ROBOT &refRobot);
	void UpdateState();

	ROBOT &Robot;

	bool printAngle, printTouch;
	uint8_t oldL2Value, oldR2Value;

private:

	
};

#endif