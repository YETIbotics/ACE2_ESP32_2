#pragma once

class CytronMD10{
	
public:

	CytronMD10(int channel, int pinpwm, int pindir, bool reversed);
	void SetMotorSpeed(float speed);

private:
	int dir = 0;	

	int _pinPWM;
	int _pinDIR;
	bool _reverse;
	int _channel;
};


