

#include "CONTROLLER.h"
#include "ROBOT.h"

CONTROLLER::CONTROLLER(ROBOT &refRobot)
	: Robot(refRobot)
{
}

void CONTROLLER::UpdateState()
{
	if (Robot.PS4.connected())
	{

		//L2 Trigger
		if (Robot.PS4.getAnalogButton(R2))
		{
			Robot.State.LiftSpeed = Robot.PS4.getAnalogButton(R2) * 1;
		}
		//R2 Trigger
		else if (Robot.PS4.getAnalogButton(L2))
		{
			Robot.State.LiftSpeed = Robot.PS4.getAnalogButton(L2) * -1;
		}
		else
		{
			Robot.State.LiftSpeed = 0;
		}

		if (Robot.PS4.getAnalogHat(LeftHatY) > 137)
		{
			//Going backwards
			Robot.State.LeftSpeed = map(Robot.PS4.getAnalogHat(LeftHatY), 137, 255, -90, -255);
		}
		else if (Robot.PS4.getAnalogHat(LeftHatY) < 117)
		{
			//going forwards
			Robot.State.LeftSpeed = map(Robot.PS4.getAnalogHat(LeftHatY), 117, 0, 90, 255);
		}
		else
		{
			Robot.State.LeftSpeed = 0;
		}

		if (Robot.PS4.getAnalogHat(RightHatY) > 137)
		{
			Robot.State.RightSpeed = map(Robot.PS4.getAnalogHat(RightHatY), 137, 255, -90, -255);
		}
		else if (Robot.PS4.getAnalogHat(RightHatY) < 117)
		{
			Robot.State.RightSpeed = map(Robot.PS4.getAnalogHat(RightHatY), 117, 0, 90, 255);
		}
		else
		{
			Robot.State.RightSpeed = 0;
		}

		if (Robot.PS4.getButtonClick(TRIANGLE))
		{
			Robot.State.LimitLift = !Robot.State.LimitLift;
		}

		if (Robot.PS4.getButtonClick(PS))
		{
			Robot.PS4.disconnect();
		}

		if (Robot.PS4.getButtonClick(UP)) {
			Robot.State.UPClick(true);
		}

		/*if (Robot.PS4.getAnalogHat(LeftHatX) > 137 || Robot.PS4.getAnalogHat(LeftHatX) < 117 || Robot.PS4.getAnalogHat(LeftHatY) > 137 || Robot.PS4.getAnalogHat(LeftHatY) < 117 || Robot.PS4.getAnalogHat(RightHatX) > 137 || Robot.PS4.getAnalogHat(RightHatX) < 117 || Robot.PS4.getAnalogHat(RightHatY) > 137 || Robot.PS4.getAnalogHat(RightHatY) < 117) {
			Serial.print(F("\r\nLeftHatX: "));
			Serial.print(Robot.PS4.getAnalogHat(LeftHatX));
			Serial.print(F("\tLeftHatY: "));
			Serial.print(Robot.PS4.getAnalogHat(LeftHatY));
			Serial.print(F("\tRightHatX: "));
			Serial.print(Robot.PS4.getAnalogHat(RightHatX));
			Serial.print(F("\tRightHatY: "));
			Serial.print(Robot.PS4.getAnalogHat(RightHatY));
		}*/

		if (Robot.PS4.getButtonClick(CROSS)) {
			Robot.PS4.setRumbleOn(RumbleLow);
		}
		if (Robot.PS4.getButtonClick(CIRCLE)) {
			Robot.PS4.setRumbleOn(RumbleHigh);
		}
		// if (Robot.PS4.getButtonClick(CROSS)) {
		// 	Serial.print(F("\r\nCross"));
		// 	Robot.PS4.setLedFlash(10, 10); // Set it to blink rapidly
		// }
		// if (Robot.PS4.getButtonClick(SQUARE)) {
		// 	Serial.print(F("\r\nSquare"));
		// 	Robot.PS4.setLedFlash(0, 0); // Turn off blinking
		// }

		// if (Robot.PS4.getButtonClick(UP)) {
		// 	Serial.print(F("\r\nUp"));
		// 	Robot.PS4.setLed(Red);
		// } if (Robot.PS4.getButtonClick(RIGHT)) {
		// 	Serial.print(F("\r\nRight"));
		// 	Robot.PS4.setLed(Blue);
		// } if (Robot.PS4.getButtonClick(DOWN)) {
		// 	Serial.print(F("\r\nDown"));
		// 	Robot.PS4.setLed(Yellow);
		// } if (Robot.PS4.getButtonClick(LEFT)) {
		// 	Serial.print(F("\r\nLeft"));
		// 	Robot.PS4.setLed(Green);
		// }

		// if (Robot.PS4.getButtonClick(L1))
		// 	Serial.print(F("\r\nL1"));
		// if (Robot.PS4.getButtonClick(L3))
		// 	Serial.print(F("\r\nL3"));
		// if (Robot.PS4.getButtonClick(R1))
		// 	Serial.print(F("\r\nR1"));
		// if (Robot.PS4.getButtonClick(R3))
		// 	Serial.print(F("\r\nR3"));

		// if (Robot.PS4.getButtonClick(SHARE))
		// 	Serial.print(F("\r\nShare"));
		// if (Robot.PS4.getButtonClick(OPTIONS)) {
		// 	Serial.print(F("\r\nOptions"));
		// 	printAngle = !printAngle;
		// }
		// if (Robot.PS4.getButtonClick(TOUCHPAD)) {
		// 	Serial.print(F("\r\nTouchpad"));
		// 	printTouch = !printTouch;
		// }

		// if (printAngle) { // Print angle calculated using the accelerometer only
		// 	Serial.print(F("\r\nPitch: "));
		// 	Serial.print(Robot.PS4.getAngle(Pitch));
		// 	Serial.print(F("\tRoll: "));
		// 	Serial.print(Robot.PS4.getAngle(Roll));
		// }

		// if (printTouch) { // Print the x, y coordinates of the touchpad
		// 	if (Robot.PS4.isTouching(0) || Robot.PS4.isTouching(1)) // Print newline and carriage return if any of the fingers are touching the touchpad
		// 		Serial.print(F("\r\n"));
		// 	for (uint8_t i = 0; i < 2; i++) { // The touchpad track two fingers
		// 		if (Robot.PS4.isTouching(i)) { // Print the position of the finger if it is touching the touchpad
		// 			Serial.print(F("X")); Serial.print(i + 1); Serial.print(F(": "));
		// 			Serial.print(Robot.PS4.getX(i));
		// 			Serial.print(F("\tY")); Serial.print(i + 1); Serial.print(F(": "));
		// 			Serial.print(Robot.PS4.getY(i));
		// 			Serial.print(F("\t"));
		// 		}
		// 	}
		// }
	}
	else
	{
		Robot.State.RightSpeed = 0;
		Robot.State.LeftSpeed = 0;
		Robot.State.LiftSpeed = 0;
	}
}
