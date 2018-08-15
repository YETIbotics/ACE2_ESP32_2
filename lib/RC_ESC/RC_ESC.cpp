
#include "RC_ESC.h"
#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>

RC_ESC::RC_ESC(int channel, Adafruit_PWMServoDriver *Refpwm, bool reversed)
{

	pwm = Refpwm;

	_isPWMBoard = true;

	_reverse = reversed;
	_channel = channel;

	pwm->setPWM(channel, 0, 1565); //342
}

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
		if (_isPWMBoard)
		{
			float startpules = map(speed, 0, 255, 2820, 4075) ;
    
    		pwm->setPWM(_channel, 0, startpules ); //342
		}
		else
			ledcWrite(_channel, map(speed, 0, 255, 4924, 6565));
		//digitalWrite(_pinPWM, HIGH);
	}
	else
	{
		if (_isPWMBoard)
		{
			float startpules = map(speed, -255, 0, 1565, 2820);
    
    		pwm->setPWM(_channel, 0, startpules ); //342
			//Serial.println(_frequency);
		}
		else
			ledcWrite(_channel, map(speed, -255, 0, 3283, 4924));
		//digitalWrite(_pinPWM, LOW);
	}
}
