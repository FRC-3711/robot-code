#include "Chassis.h"
#include "../Robotmap.h"
#include "../Commands/Drive.h"

// Constructor for the Chassis class
Chassis::Chassis() : Subsystem("Chassis")
{
	// Create an instance of the RobotDrive class for Mecanum drive (front left, rear left, front right, rear right)
	drive = new RobotDrive(DRIVE_FRONT_LEFT, DRIVE_BACK_LEFT, DRIVE_FRONT_RIGHT, DRIVE_BACK_RIGHT);
	
	// Disable safety mode (are we sure we want to do this?)
	drive->SetSafetyEnabled(false);

	// Right side motors have to spin backward from the left (relative to motor)
	// Can't wire them backward; won't pass inspection
	drive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
	drive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
}

void Chassis::InitDefaultCommand()
{
	// Drive command will run all the time to handle drive input
	// Can be overruled by another command being started that requires this subsystem
	SetDefaultCommand(new Drive());
}


// MecanumDrive_Cartesian (float x, float y, float rotation, float gyroAngle = 0.0 )
void Chassis::mecanumDrive(float x, float y, float z, float headingAngle)
{
	// Mecanum drive handles three-axis steering. Passing 0 for gyro disables field-centric drive.
	drive->MecanumDrive_Cartesian(x, y, z, 0);
}

/* Tank and Arcade drive will not be used this year
// Sends a speed signal to the drive motors (Tank Drive/dual-stick mode)
void Chassis::tankDrive(double left, double right)
{
	drive -> TankDrive(left, right);
}

// Sends a speed signal to the drive motors (Arcade/Single stick drive mode)
void Chassis::arcadeDrive(Joystick *stickPosition)
{
	drive -> ArcadeDrive(stickPosition);
}
*/
