#ifndef STATE_h
#define STATE_h

#include <Arduino.h>

class STATE
{

  public:
	STATE();

	float GetLeftSpeedPercent();
	float GetRightSpeedPercent();

	
	int8_t Temp = 0;

	float Volts0 = 0;
	float Volts1 = 0;
	float Volts2 = 0;

	float Amps0 = 0;
	float Amps1 = 0;

	float LeftSpeed = 0;
	float RightSpeed = 0;
	float LiftSpeed = 0;

	int32_t LeftEnc = 0;
	int32_t RightEnc = 0;
	int32_t LiftEnc = 0;

	bool LimitLift = true;
	static const int LiftLimitMax = 20;

	bool UPClick(bool setState);

	bool OIControl = true;

	float Heading();
	void UpdateHeading(float newHeading);	

	String USBState = "";

  private:
	bool _UPClick = false;

	
	float _gyroDegrees;
	int _gyroRotations = 0;
};

#endif