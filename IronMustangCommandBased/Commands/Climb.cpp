#include "Climb.h"

static bool StickIsClimbMode;
static float ClimbRate;

Climb::Climb()
{
	// Use requires() here to declare subsystem dependencies
	Requires(climber);
}

// Called just before this Command runs the first time
void Climb::Initialize()
{
	
}

// Called repeatedly when this Command is scheduled to run
void Climb::Execute()
{
	// check if the climber button has changed status
	if (oi->checkClimberButton())
	{
		// flag the status
		StickIsClimbMode = true;
	}
	else
	{
		// flag the status
		StickIsClimbMode = false;
	}
	
	// if the stick is in climb mode, actuate the motors
	if (StickIsClimbMode)
	{	
		ClimbRate = oi->getShooterLiftRate();
		
		// Invert the joystick to comply with Terry's joystick commandment
		//ClimbRate *= -1;

		// when the shooter stick is in climb mode, apply it's value to the climb motors
		climber->setClimbRate(ClimbRate);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool Climb::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void Climb::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Climb::Interrupted() {
}
