#include "AUTONOMOUS.h"
#include "ROBOT.h"

AUTONOMOUS::AUTONOMOUS(ROBOT &refRobot) : Robot(refRobot)
{
}

void AUTONOMOUS::Loop()
{
    if (Robot.State.UPClick(false))
    {
        RunSkillsAuton();
    }


}

void AUTONOMOUS::RunSkillsAuton()
{
    Robot.State.OIControl = false;
    //Drive backwards and take out the cones
    //Robot.Lift.ToAbsolute(25);
    //delay(500);

    Robot.Drive.ToRelative(240, 255, 255);
    while(Robot.Drive.PercentComplete < 100){ delay(20); }

    Robot.Lift.ToAbsolute(20);
    while(Robot.Lift.PercentComplete < 100){ delay(20); }

    Robot.Drive.ToRelative(-40, 100, 100);
    while(Robot.Drive.PercentComplete < 100){ delay(20); }

    Robot.Drive.ToRelative(-140, 255, 255);
    while(Robot.Drive.PercentComplete < 100){ delay(20); }

    Robot.Drive.TurnRelative(-240);
    while(Robot.Drive.PercentComplete < 100){ delay(20); }

    Robot.Drive.ToRelative(50, 255, 255);
    while(Robot.Drive.PercentComplete < 100){ delay(20); }

    Robot.Drive.ToRelative(-50, 255, 255);
    while(Robot.Drive.PercentComplete < 100){ delay(20); }
    /*
    AutoTask at = drive->ToAsync(-1000); 
    while(at.PercentComplete < 100){ delay(20); }

    //turn ccw to aim at MOGO (do Synchronously)
    Drive.Turn(-20);

    //Drive forward to grab MOGO
    Drive.To(50);

    //Pick up MOGO
    int LiftTaskPercentComplete = Lift.ToAsync(40);
    //Wait until lift is halfway up then move backward.
    while(LiftTaskPercentComplete < 50){ delay(20); }

    //sweep turn will integrate distance and rotation
    //Backup 50 while turning 20 degrees.
    Drive.Sweep(-50, 20);

    //should be pointing at the other MOGO now.
    //drive forward, override PID constants to not slow down. We'll capture the end.
    Drive.To(900, STOPABRUPT);
    //Want to throw mogo, stop abruptly, apply some backward force.
    //Drive.Speed(-150, -150);
    //delay(50);
    //Drive.Speed(0,0);

    //scoop up other mogo and score in 10.
    Drive.To(-100);
    Lift.To(0);
    Drive.To(90);
    Lift.To(20);
    Drive.To(20, STOPABRUPT);
*/
    Robot.State.OIControl = true;
}