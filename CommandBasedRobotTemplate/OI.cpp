#include "OI.h"
#include "Robotmap.h"
#include "Commands/Fire.h"
#include "Commands/AngleControl.h"

OI::OI()
{
	// Process operator interface input here.
	
	// Create new Joystick instances for all joysticks. These must be declared in the header.
	// 2014 robot uses driver (Logitech Extreme 3D) and shooter (Logitech Attack 3)
	driver_stick = new Joystick(DRIVE_STICK_PORT);
	shooter_stick = new Joystick(SHOOTER_STICK_PORT);
	
	// Map buttons that will fire atomic commands. These must be declared in the header.
	shooter_trigger = new JoystickButton(shooter_stick, SHOOTER_TRIGGER);
	// Bind commands to button events
	shooter_trigger->WhenActive(new AngleControl(340.0));
	shooter_trigger->WhenReleased(new Fire());
	
	shooter_zero = new JoystickButton(shooter_stick, SHOOTER_ZERO_BUTTON);
	shooter_zero->WhenActive(new AngleControl(0.0));
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
