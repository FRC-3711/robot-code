#include "Chassis.h"
#include "../Robotmap.h"
#include "../Commands/Drive.h"

// Constructor for the Chassis class
Chassis::Chassis() : Subsystem("Chassis")
{
	// Create an instance of the RobotDrive class
	drive = new RobotDrive(LEFT_DRIVE_MOTOR, RIGHT_DRIVE_MOTOR); // (leftmotor, rightmotor channel)
	
	// Disable safety mode (are we sure we want to do this?)
	drive -> SetSafetyEnabled(false);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Chassis::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new Drive());
}

// Sends a speed signal to the drive motors (Tank Drive/dual-stick mode)
void Chassis::tankDrive(double left, double right)
{
	drive -> TankDrive(left, right);
}

// Sends a speed signal to the drive motors (Arcade/Single stick drivem mode)
void Chassis::arcadeDrive(Joystick *stickPosition)
{
	drive -> ArcadeDrive(stickPosition);
}
