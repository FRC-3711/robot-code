#include "Climber.h"
#include "../Robotmap.h"
#include "../Commands/Climb.h"

Climber::Climber() : Subsystem("Climber")
{
	// Create an instance of the Talon class to control the climbing motors
	climber_motor_1 = new Talon(CLIMB_MOTOR_1);
	climber_motor_2 = new Talon(CLIMB_MOTOR_2);
	
	// Climber uses a limit switch
	switch_climb = new DigitalInput(LIMIT_CLIMB);
	
}
    
void Climber::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new Climb());
}

// Extend or retract the climbing mechanism. The limit switches are integrated with this function
// and not called seperately
void Climber::setClimbRate(float climb_rate)
{
	bool switch_status;
	
	// check the limit switch
	switch_status = switch_climb->Get();
	
	// If the switch is engaged, don't allow the motor to retract
	if ((!switch_status) && (climb_rate > 0))
	{
		climber_motor_1->Set(0);
		climber_motor_2->Set(0);
	}
	// otherwise allow the motors to move freely
	else
	{
		climber_motor_1->Set(climb_rate);
		climber_motor_2->Set(climb_rate);
	}
}
