
#include "ROBOT.h"

ROBOT::ROBOT() : Btd(&Usb), PS4(&Btd), Drive(*this), Controller(*this), Lift(*this), Autonomous(*this)
{
}

void ROBOT::Setup()
{

	Usb.Init();

	

	lastStateUpdate = millis();
}

void ROBOT::Loop()
{
	State.USBState = "In Task";
	Usb.Task();
	State.USBState = "";

	if (State.OIControl)
		Controller.UpdateState();
}
