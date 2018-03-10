
#include "STATE.h"
#include <Arduino.h>

STATE::STATE()
{
}

bool STATE::UPClick(bool setState)
{
	if (_UPClick)
	{
		_UPClick = false;
		return true;
	}

	_UPClick = setState;

	return false;
}

float STATE::GetLeftSpeedPercent()
{
	return map(LeftSpeed, -255, 255, -99, 99);
}

float STATE::GetRightSpeedPercent()
{
	return map(RightSpeed, -255, 255, -99, 99);
}

void STATE::UpdateHeading(float newHeading)
{
	float prev = _gyroDegrees;
	float dif = prev - newHeading;
	if (abs(dif) > 180)
	{
		if (dif < 0)
		{
			_gyroRotations--; 
		}
		else
		{
			_gyroRotations++;
		}
	}

	_gyroDegrees = newHeading;
}

float STATE::Heading() {
	return _gyroDegrees + (360 * _gyroRotations);
}
