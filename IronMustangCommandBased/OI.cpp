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

float OI::getDriverLeftStick()
{	
	return driver_stick->GetY();
}

float OI::getDriverRightStick()
{
	return driver_stick->GetRawAxis(4);
}

// Checks if the shooter motor enable button is pressed
bool OI::checkShooterMotorEnable()
{	
	return shooter_stick->GetRawButton(SHOOTER_MOTOR_ENABLE);
}

// Checks if the shooter motor disable button is pressed
bool OI::checkShooterMotorDisable()
{
	return shooter_stick->GetRawButton(SHOOTER_MOTOR_DISABLE);
}

// Checks if the shooter trigger is pressed
bool OI::checkShooterTrigger()
{
	return shooter_stick->GetRawButton(SHOOTER_TRIGGER);
}

// Checks if the climber button is enabled
bool OI::checkClimberButton()
{
	return shooter_stick->GetRawButton(CLIMBER_BUTTON);
}


// Check the position of the motor speed control
float OI::getShooterMotorSpeed()
{
	float position; // the position of the axis
	
	// obtain axis position, result will be -1 to 1 where -1 is full up
	position = shooter_stick->GetRawAxis(SHOOTER_SPEED_AXIS);
	
	// invert the axis since it's easier to think about full up as being +1
	position *= -1;
	
	// add one to the result to get a non negative number from 0 to 2
	position += 1;
	
	// now scale the result to make it between 0 and 1
	position *= 0.5;

	// invert the position because the motors are hooked up backward
	position *= -1;
	
	return position;
}

float OI::getShooterLiftRate()
{
	float position;
	
	position = (-1*shooter_stick->GetY());
	
	// shape position to assume a deadband
	if ((position >= -0.2) && (position <= 0.2))
	{
		return 0;
	}
	else
	{
		return position;
	} 
}
