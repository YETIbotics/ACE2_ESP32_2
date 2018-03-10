#include "DRIVE.h"
#include "ROBOT.h"

DRIVE::DRIVE(ROBOT &refRobot) : Robot(refRobot), RightEnc(Robot._RightEnc0, Robot._RightEnc1), LeftEnc(Robot._LeftEnc0, Robot._LeftEnc1), DriveRight(7, Robot._LeftPWM, Robot._LeftDIR, false), DriveLeft(6, Robot._RightPWM, Robot._RightDIR, true)
{
}

void DRIVE::Loop()
{
    Robot.State.RightEnc = RightEnc.read();
    Robot.State.LeftEnc = LeftEnc.read();

    if (_ToSetPointEnabled)
    {
        //move to point
        if (_ToSetPoint > RightEnc.read())
        {
            //Go up
            while (_ToSetPoint > RightEnc.read())
            {
                DriveLeft.SetMotorSpeed(_atLeftSpeed);
                DriveRight.SetMotorSpeed(_atRightSpeed);

                delay(20);
            }
        }
        else
        {
            //go down
            while (_ToSetPoint < RightEnc.read())
            {
                DriveLeft.SetMotorSpeed(-_atLeftSpeed);
                DriveRight.SetMotorSpeed(-_atRightSpeed);

                delay(20);
            }
        }

        _ToSetPoint = 0;
        _ToSetPointEnabled = false;
        PercentComplete = 100;
    }

    //THIS IS THE GYRO BASED TURN
    // if (_TurnSetPointEnabled)
    // {
    //     //move to point
    //     if (_TurnSetPoint > Robot.State.Heading())
    //     {
    //         //Go up
    //         DriveLeft.SetMotorSpeed(150);
    //         DriveRight.SetMotorSpeed(-150);
    //         while (_TurnSetPoint > Robot.State.Heading())
    //         {
    //             delay(20);
    //         }
    //     }
    //     else
    //     {
    //         //go down
    //         DriveLeft.SetMotorSpeed(-150);
    //         DriveRight.SetMotorSpeed(150);
    //         while (_TurnSetPoint < Robot.State.Heading())
    //         {
    //             delay(20);
    //         }
    //     }

    //     _TurnSetPoint = 0;
    //     _TurnSetPointEnabled = false;
    //     PercentComplete = 100;
    // }

    //GOING TO DO ESTIMATED ENCODER BASED TURN
    if (_TurnSetPointEnabled)
    {
        //move to point
        // if (_TurnSetPoint > RightEnc.read())
        // {
        //     //Go up
        //     DriveLeft.SetMotorSpeed(-150);
        //     //DriveRight.SetMotorSpeed(150);
        //     while (_TurnSetPoint > LeftEnc.read())
        //     {
        //         delay(20);
        //     }
        // }
        // else
        // {
            //go down
            DriveLeft.SetMotorSpeed(0);
            DriveRight.SetMotorSpeed(-150);
            while (_TurnSetPoint < RightEnc.read())
            {
                delay(20);
            }
        // }

        _TurnSetPoint = 0;
        _TurnSetPointEnabled = false;
        PercentComplete = 100;
    }

    DriveRight.SetMotorSpeed(Robot.State.RightSpeed);
    DriveLeft.SetMotorSpeed(Robot.State.LeftSpeed);

  
}

void DRIVE::ToRelative(int pos, int leftSpeed, int rightSpeed)
{
    PercentComplete = 0;
    _ToSetPointEnabled = true; 
    _ToSetPoint = RightEnc.read() + pos; 
    _atLeftSpeed = rightSpeed;
    _atRightSpeed = leftSpeed; 
}

void DRIVE::TurnRelative(float degrees)
{
    PercentComplete = 0;
    _TurnSetPointEnabled = true;
    // _TurnSetPoint = Robot.State.Heading() + degrees;

    _TurnSetPoint = RightEnc.read() + degrees;
}

AutoTask &DRIVE::ToAsync(int distance)
{
    return autoTask;
}