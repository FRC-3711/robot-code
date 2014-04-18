#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/Autonomous.h"
#include "Commands/Drive.h"
#include "Commands/Shoot.h"
#include "Commands/SampleSensors.h"
#include "CommandBase.h"
#include "Robotmap.h"

class CommandBasedRobot : public IterativeRobot
{
public:
	Gyro *gyro;
	
private:
	Autonomous *autonomousCommand;
	Drive *driveCommand;
	Shoot *shootCommand;
	SampleSensors *sampleSensors;
	LiveWindow *lw;

	virtual void RobotInit() 
	{
		CommandBase::init();
		
		// Create an instance of the Compressor to feed frisbees into the motor
		autonomousCommand = new Autonomous();
		driveCommand = new Drive();
		shootCommand = new Shoot();
		sampleSensors = new SampleSensors();
		lw = LiveWindow::GetInstance();
		
		// Initialize the gyro, connected to analog module 1, analog channel 1
		
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
		sampleSensors->Start();
		
		sampleSensors->ResetHeading();
	}
	
	virtual void TeleopPeriodic() {
		Scheduler::GetInstance()->Run();
	}
	
	virtual void TestPeriodic() {
		lw->Run();
	}
};

START_ROBOT_CLASS(CommandBasedRobot);

