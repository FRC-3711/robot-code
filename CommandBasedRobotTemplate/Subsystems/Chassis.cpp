#include "Chassis.h"
#include "../Robotmap.h"
#include "../Commands/Drive.h"

// Constructor for the Chassis class
Chassis::Chassis() : Subsystem("Chassis")
{
	// Create an instance of the RobotDrive class for Mecanum drive (front left, rear left, front right, rear right)
	drive = new RobotDrive(DRIVE_FRONT_LEFT, DRIVE_BACK_LEFT, DRIVE_FRONT_RIGHT, DRIVE_BACK_RIGHT);
	
	// Disable safety mode (are we sure we want to do this?)
	drive -> SetSafetyEnabled(false);
	drive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	drive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
}

void Chassis::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new Drive());
}


// MecanumDrive_Cartesian (float x, float y, float rotation, float gyroAngle = 0.0 )
void Chassis::mecanumDrive(float x, float y, float z, float headingAngle)
{
	drive->MecanumDrive_Cartesian(x, y, z, 0);
}

/* Tank and Arcade drive will not be used this year
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
*/
