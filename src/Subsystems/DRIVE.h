#pragma once

#include<Autonomous/AutoTask.h>
#include <CytronMD10.h>
#include <Encoder.h>

class ROBOT;

class DRIVE{
	
public:

	DRIVE(ROBOT &refRobot);
	void Loop();
	void ToRelative(int pos, int leftSpeed, int rightSpeed);
	void TurnRelative(float degrees);
    AutoTask& ToAsync(int distance);

	Encoder LeftEnc;
	Encoder RightEnc;
	CytronMD10 DriveRight;
	CytronMD10 DriveLeft;

	int PercentComplete = 100;

private:
	ROBOT &Robot;
	AutoTask autoTask;

	int _atLeftSpeed;
	int _atRightSpeed;
	
	bool _ToSetPointEnabled = false;
	int _ToSetPoint = 0;

	bool _TurnSetPointEnabled = false;
	float _TurnSetPoint = 0;
};


