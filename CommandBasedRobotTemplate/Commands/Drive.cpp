#include "Drive.h"
#include <math.h>

static bool Driving = false;

Drive::Drive() {
	// Use requires() here to declare subsystem dependencies
	Requires(chassis);
	Autonomous = false;
}

// Called just before this Command runs the first time
void Drive::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute()
{
	float StickX;	// Joystick X axis (used for strafe)
	float StickY;   // Joystick Y axis (used for fwd/rev)
	float StickZ;	// Joystick Z axis (used for rotation)
	float Heading;	// Gyro heading
	
	// Gets a pointer to the LCD instance
	DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();
	
	// Get current stick positions and calculated gyro heading
	StickX = oi->getDriveStrafeStick();
	StickY = oi->getDriveFwdStick();
	StickZ = oi->getDriveRotationStick();
	
	// Add expo to the X and Y axes
	StickX = pow(StickX, 3);
	StickY = pow(StickY, 3);
	StickZ = pow(StickZ, 9) * 0.5;
	
	dsLCD->UpdateLCD();
	
	// Pass the stick and sensor data to the mecanum function of the RobotDrive class
	if (StickX != 0.0 || StickY != 0.0 && StickZ != 0.0) {
		chassis->mecanumDrive(StickX, StickY, StickZ, Heading);
		Driving = true;
	}
	else if (Driving)
	{
		chassis->mecanumDrive(StickX, StickY, StickZ, Heading);
		Driving = false;
	}
}

//drivetrain.TankDrive(joystick.GetY(), joystick.GetRawAxis(5);
// Make this return true when this Command no longer needs to run execute()
bool Drive::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void Drive::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Drive::Interrupted() {
}
