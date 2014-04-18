#include "FrisbeeLauncher.h"
#include "../Robotmap.h"
#include "../Commands/Shoot.h"

#define OPEN_POSITION 0.5
#define CLOSED_POSITION 0.0

// Constructor for the FrisbeeLauncher Class
FrisbeeLauncher::FrisbeeLauncher() : Subsystem("FrisbeeLauncher")
{
	// Create an instance of the Talon class to control the shooter motor
	shooter_motor_1 = new Talon(SHOOTER_MOTOR_1);
	shooter_motor_2 = new Talon(SHOOTER_MOTOR_2);
	shot_gate = new Servo(SERVO_MOTOR_1);

	// Create an instance of the Talon class to control the shooter tilt
	tilt_motor = new Victor(TILT_MOTOR);
	
	// Instantiate the solenoid class to fire the frisbees into the launch mechanism
	solenoid = new Solenoid(SOLENOID);

	// Set up limit switch classes
	switch_high = new DigitalInput(LIMIT_SWITCH_HIGH);
	switch_low = new DigitalInput(LIMIT_SWITCH_LOW);
}
    
void FrisbeeLauncher::InitDefaultCommand()
{
	// Set the default command Class for a subsystem here.
	SetDefaultCommand(new Shoot());
}

// Turn off the Shooter motor (to save battery life)
void FrisbeeLauncher::disableShooterMotor(void)
{
	//Set the PWM to 0, effectively disabling the motor
	shooter_motor_1->Set(0);
	shooter_motor_2->Set(0);
}

void FrisbeeLauncher::fire(bool fire)
{
	solenoid->Set(fire);
}

// Turn on the shooter motor and map to the position of the speed control on the joystick
void FrisbeeLauncher::setShooterMotorSpeed(float speed)
{
	// Set the speed of the shooter motor
	shooter_motor_1->Set(speed);
	shooter_motor_2->Set(speed);
}

// Position the shooter elevation/tilt mechanism
void FrisbeeLauncher::setElevationRate(float lift_rate)
{	
	tilt_motor->Set(lift_rate);
}

bool FrisbeeLauncher::getSwitchHigh(void)
{
	bool result;
	
	result = switch_high->Get();
	
	if (result)
		result = FALSE;
	else
		result = TRUE;

	return result;
}

bool FrisbeeLauncher::getSwitchLow(void)
{
	bool result;
	
	result = switch_low->Get();
	
	if (result)
		result = FALSE;
	else
		result = TRUE;
	
	return result;
	
}

void FrisbeeLauncher::openShotGate(void)
{
	shot_gate->Set(OPEN_POSITION);
}

void FrisbeeLauncher::closeShotGate(void)
{
	shot_gate->Set(CLOSED_POSITION);
}


