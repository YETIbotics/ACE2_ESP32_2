#pragma once

class ROBOT;

class AUTONOMOUS{
	
public:

	AUTONOMOUS(ROBOT &refRobot);
    void RunSkillsAuton();
    void Loop();


private:
    ROBOT &Robot;
	
};


