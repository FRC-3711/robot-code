#include "WhipperSnapper.h"
#include "../Robotmap.h"
#include "../Commands/Shoot.h"

// Constructor for the WhipperSnapper Class
WhipperSnapper::WhipperSnapper() : Subsystem("WhipperSnapper")
{
	// Create an instance of the Talon class to control the shooter motor
	shooter_motor_1 = new Talon(SHOOTER_MOTOR_1);
	shooter_motor_2 = new Talon(SHOOTER_MOTOR_2);
	
	loader_motor = new Talon(LOADER_MOTOR);
}

void WhipperSnapper::InitDefaultCommand()
{
	// Set the default command Class for a subsystem here.
	SetDefaultCommand(new Shoot());
}

// Turn off the Shooter motor
void WhipperSnapper::MotorOff(void)
{
	//Set the PWM to 0, effectively disabling the motor
	shooter_motor_1->Set(0);
	shooter_motor_2->Set(0);
}

// Turn on the shooter motor and map to the position of the speed control on the joystick
void WhipperSnapper::SetMotorSpeed(float speed)
{
	// Set the speed of the shooter motor
	shooter_motor_1->Set(speed);
	shooter_motor_2->Set(speed);
}

void WhipperSnapper::StartLoader()
{
	loader_motor->Set(1.0);
}

void WhipperSnapper::ReverseLoader()
{
	loader_motor->Set(-1.0);
}

void WhipperSnapper::StopLoader()
{
	loader_motor->Set(0.0);
}

