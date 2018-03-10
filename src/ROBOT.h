#ifndef ROBOT_h
#define ROBOT_h

#include <Wire.h>

#include <PS4BT.h>
#include <usbhub.h>
// #include <utility\imumaths.h>


#include <STATE.h>
#include <Subsystems\CONTROLLER.h>
#include <Subsystems\DRIVE.h>
#include <Subsystems\LIFT.h>
#include <Autonomous\AUTONOMOUS.h>

class ROBOT
{
  public:
	ROBOT();

	void Setup();
	void Loop();

	unsigned long lastStateUpdate;

	//USB and PS4 Items
	USB Usb;
	BTD Btd;
	PS4BT PS4;

	//Subsystems
	STATE State;
	CONTROLLER Controller;
	DRIVE Drive;
	LIFT Lift;
	AUTONOMOUS Autonomous; 

	//SENSORS AND MOTORS
	



	

	//PIN Declarations
	static const int _LeftEnc0 = 34;
	static const int _LeftEnc1 = 35;
	static const int _RightEnc0 = 36;
	static const int _RightEnc1 = 39;
	static const int _LiftEnc0 = 33;
	static const int _LiftEnc1 = 32;
	//static const int _LEDRing = 25;
	static const int _LiftPWM = 13;
	//static const int _Acc1PWM = 27;
	//static const int _Acc2PWM = 14;

	static const int _RightPWM = 26;
	static const int _RightDIR = 27;
	static const int _LeftPWM = 14;
	static const int _LeftDIR = 12;

	static const int _Button0 = 0;
	static const int _LEDBuiltIn = 25;

  private:
};

#endif