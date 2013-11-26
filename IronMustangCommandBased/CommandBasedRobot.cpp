#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/Autonomous.h"
#include "Commands/Drive.h"
#include "Commands/Shoot.h"
#include "Commands/Climb.h"
#include "CommandBase.h"
#include "Robotmap.h"

class CommandBasedRobot : public IterativeRobot
{
	
	
private:
	Command *autonomousCommand;
	Drive *driveCommand;
	Shoot *shootCommand;
	Climb *climbCommand;
	Compressor *compressor;
	LiveWindow *lw;
	
	virtual void RobotInit() {
		CommandBase::init();
		
		// Create an instance of the Compressor to feed frisbees into the motor
		compressor = new Compressor(COMPRESSOR_SWITCH, COMPRESSOR_RELAY); 
		autonomousCommand = new Autonomous();
		driveCommand = new Drive();
		shootCommand = new Shoot();
		climbCommand = new Climb();
		lw = LiveWindow::GetInstance();
		
		// start the compressor
		compressor->Start();
	}
	
	virtual void AutonomousInit() {
		autonomousCommand->Start();
	}
	
	virtual void AutonomousPeriodic() {
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TeleopInit()
	{
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (autonomousCommand)
		{			
			// cancel the autonomous mode
			autonomousCommand->Cancel();
		}
		
		// start the commands used for Teleop
		driveCommand->Start();
		shootCommand->Start();
		climbCommand->Start();
	}
	
	virtual void TeleopPeriodic() {
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TestPeriodic() {
		lw->Run();
	}
};

START_ROBOT_CLASS(CommandBasedRobot);

