#include "OI.h"
#include "Robotmap.h"
//#include "Commands/"

OI::OI()
{
	// Process operator interface input here.
	
	// Create an instance of the Joystick class for the Dual (driver) Joystick PORT 1
	driver_stick = new Joystick(DRIVE_STICK_PORT);
	
	// Create an instance of the Joystick class for the ATK3 (shooter) Joystick PORT 2
	shooter_stick = new Joystick(SHOOTER_STICK_PORT);
}

Joystick * OI::getJoystick()
{
	return driver_stick;
}

float OI::getAxis(uint32_t axis)
{
	return driver_stick->GetRawAxis(axis);
}

float OI::getDriveFwdStick()
{	
	return driver_stick->GetRawAxis(STICK_FWD_AXIS);
}

float OI::getDriveStrafeStick()
{
	return driver_stick->GetRawAxis(STICK_STRAFE_AXIS);
}

float OI::getDriveRotationStick()
{
	return driver_stick->GetRawAxis(STICK_ROTATE_AXIS);
}

bool OI::checkShooterCalibrateForward()
{
	return shooter_stick->GetRawButton(CALIBRATE_FORWARD_BUTTON);
}

bool OI::checkLoaderLoadButton()
{
	return shooter_stick->GetRawButton(LOADER_LOAD_BUTTON);
}

bool OI::checkLoaderReverseButton()
{
	return shooter_stick->GetRawButton(LOADER_REVERSE_BUTTON);
}

bool OI::checkShooterCalibrateReverse()
{
	return shooter_stick->GetRawButton(CALIBRATE_REVERSE_BUTTON);
}

bool OI::checkShooterCalibrateEnable()
{
	return shooter_stick->GetRawButton(CALIBRATE_ENABLE_BUTTON);
}

// Checks if the shooter trigger is pressed
bool OI::checkShooterTrigger()
{
	//return shooter_stick->GetRawButton(SHOOTER_TRIGGER);
	return shooter_stick->GetRawButton(SHOOTER_TRIGGER);
}


// Check the position of the motor speed control
float OI::getShooterMotorSpeed()
{
	float position; // the position of the axis
	
	// obtain axis position, result will be -1 to 1 where -1 is full up
	position = shooter_stick->GetRawAxis(SHOOTER_SPEED_AXIS);
	
	// invert the axis since it's easier to think about full up as being +1
	position *= -1;
	
	// now scale the result to make it between 0 and 1
	position *= 0.1;
	
	position += 0.9;
	
	return position;
}

float OI::getShooterMoveRate()
{
	return shooter_stick->GetRawAxis(SHOOTER_MOVE_AXIS);
}
