#pragma once

class RC_ESC{
	
public:

	RC_ESC(int channel, int pinpwm, bool reversed);
	void SetMotorSpeed(float speed);

private:

	int _pinPWM;
	bool _reverse;
	int _channel;
};


