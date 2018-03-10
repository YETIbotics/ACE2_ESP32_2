
#include "RC_ESC.h"
#include <Arduino.h>


//https://hackaday.com/2016/10/31/whats-new-esp-32-testing-the-arduino-esp32-library/
RC_ESC::RC_ESC(int channel, int pinpwm, bool reversed)
{
	_pinPWM = pinpwm;
	_reverse = reversed;
	_channel = channel;

	pinMode(_pinPWM, OUTPUT);
	//digitalWrite(_pinPWM, HIGH);

	//doing this because it seems to initialize the timer correclty... TODO: More research in to why?
	//ledcSetup(5, 20000, 8);

	ledcSetup(_channel, 50, 16);
	ledcAttachPin(_pinPWM, _channel);
	ledcWrite(_channel, 4924);
}

void RC_ESC::SetMotorSpeed(float speed)
{
	if (_reverse)
		speed = speed * -1;

	if (speed > 0)
	{
		ledcWrite(_channel, map(speed, 0, 255, 4924, 6565));
		//digitalWrite(_pinPWM, HIGH);
	}
	else
	{
		ledcWrite(_channel, map(speed, -255, 0, 3283, 4924));
		//digitalWrite(_pinPWM, LOW);
	}
}
