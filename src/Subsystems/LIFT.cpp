#include "LIFT.h"
#include "ROBOT.h"

LIFT::LIFT(ROBOT &refRobot) : Robot(refRobot), LiftEnc(Robot._LiftEnc0, Robot._LiftEnc1)//, Lift(2, &Robot.pwm, true) // Lift(0, Robot._LiftPWM, true)
{
}

void LIFT::Loop()
{
    Robot.State.LiftEnc = liftPos();

    if(_GoToSetPoint)
    {
        //move to point 
        if(_SetPoint > liftPos())
        {
            //Go up
            while(_SetPoint > liftPos())
            {
                //Lift.SetMotorSpeed(150);

                delay(20);
            }
        }
        else
        {
            //go down
            while(_SetPoint < liftPos())
            {
                //Lift.SetMotorSpeed(-150);

                delay(20);
            }
        }

        _SetPoint = 0;
        _GoToSetPoint = false;
        PercentComplete = 100;
    }

    if (Robot.State.LimitLift)
    {
        if ((Robot.State.LiftEnc >= 20 && Robot.State.LiftSpeed > 0) || Robot.State.LiftEnc <= 0 && Robot.State.LiftSpeed < 0)
        {
            Robot.State.LiftSpeed = 0;
        }
    }

    //Lift.SetMotorSpeed(Robot.State.LiftSpeed * .75);


}

void LIFT::ToAbsolute(int pos)
{
    PercentComplete = 0;
    _GoToSetPoint = true;
    _SetPoint = pos;
}

AutoTask &LIFT::ToAsync(int distance)
{
    return autoTask;
}

int32_t LIFT::liftPos()
{
    int32_t curpos = LiftEnc.read();
    if (curpos < liftMin)
        liftMin = curpos;

    return curpos - liftMin;
}