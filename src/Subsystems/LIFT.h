#pragma once

#include<Autonomous/AutoTask.h>
#include <RC_ESC.h>
#include <Encoder.h>

class ROBOT;

class LIFT{
	
public:

	LIFT(ROBOT &refRobot);
	void Loop();
	int32_t liftPos();
	void ToAbsolute(int pos);
    AutoTask& ToAsync(int distance);

	Encoder LiftEnc;
	RC_ESC Lift;

	int32_t liftMin = 0;

	int PercentComplete = 100;

private:
	ROBOT &Robot;
	AutoTask autoTask;

	bool _GoToSetPoint = false;
	int _SetPoint = 0;
};


