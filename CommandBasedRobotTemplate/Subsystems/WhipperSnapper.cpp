#include "WhipperSnapper.h"
#include "../Robotmap.h"
#include "../Commands/Shoot.h"

WhipperSnapper::WhipperSnapper() : Subsystem("WhipperSnapper")
{
	// Actually two Talons and two 2.5" CIMs, but only one channel
	shooter_motor_1 = new Talon(SHOOTER_MOTOR_1);
	
	// AndyMark gear motor
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
}

// Turn on the shooter motor and map to the position of the speed control on the joystick
void WhipperSnapper::SetMotorSpeed(float speed)
{
	// Set the speed of the shooter motor
	shooter_motor_1->Set(speed);
}

// Loader normally spins toward inside of robot
void WhipperSnapper::StartLoader()
{
	loader_motor->Set(1.0);
}

// Allows loader to be run in reverse to dump ball quickly from robot
void WhipperSnapper::ReverseLoader()
{
	loader_motor->Set(-1.0);
}

// Stops loader; convenience/readability method
void WhipperSnapper::StopLoader()
{
	loader_motor->Set(0.0);
}
