
#include "CytronMD10.h"
#include <Arduino.h>

CytronMD10::CytronMD10(int channel, int pinpwm, int pindir, bool reversed)
{
	_pinPWM = pinpwm;
	_pinDIR = pindir;
	_reverse = reversed;
	_channel = channel;

	pinMode(_pinDIR, OUTPUT);
	pinMode(_pinPWM, OUTPUT);

	ledcSetup(_channel, 20000, 8);
	ledcAttachPin(_pinPWM, _channel);
}

void CytronMD10::SetMotorSpeed(float speed)
{
	if (speed > 0)
		dir = 1;
	else
		dir = 0;

	if (_reverse)
		dir = (dir - 1) * -1;

	digitalWrite(_pinDIR, dir);
	ledcWrite(_channel, abs(speed));
}
