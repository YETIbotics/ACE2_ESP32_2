#pragma once

class Adafruit_PWMServoDriver;

class RC_ESC{
	
public:

	RC_ESC(int channel, int pinpwm, bool reversed);
	RC_ESC(int channel, Adafruit_PWMServoDriver *Refpwm, bool reversed);
	void SetMotorSpeed(float speed);

private:
	Adafruit_PWMServoDriver *pwm;

	bool _isPWMBoard = false;
	float _frequency = 500;

	int _pinPWM;
	bool _reverse;
	int _channel;

};


