#include "WhipperSnapper.h"
#include "../Robotmap.h"
#include "../Commands/ShooterControl.h"

WhipperSnapper::WhipperSnapper() : PIDSubsystem("WhipperSnapper", 1.0, 0.01, 0.0)
{
	// Configure the PID controller to always take the shortest route even if it involves passing through 0
	GetPIDController()->SetContinuous(true);
	this->SetAbsoluteTolerance(1.0);
	
	// Actually two Talons and two 2.5" CIMs, but only one channel
	shooter_motor_1 = new Talon(SHOOTER_MOTOR_1);
	
	// AndyMark gear motor
	loader_motor = new Talon(LOADER_MOTOR);
	
	// Shooter encoder
	shooter_encoder = new Encoder360(SHOOTER_ENCODER_CHA, SHOOTER_ENCODER_CHB, true);
	shooter_encoder->SetDistancePerPulse(12.0 / 45.0 / 360.0); // 360 pulses per axle rotation; 45:12 reduction to arm
	shooter_encoder->SetMinRate(1.0); //arbitrary; sets lowest threshold of pulses/s before encoder shows "stopped"
	shooter_encoder->Start();
	shooter_photoeye = new DigitalInput(SHOOTER_PHOTOEYE);
}

void WhipperSnapper::InitDefaultCommand()
{
	// Set the default command Class for a subsystem here.
	// This command will run whenever the subsystem is idle; i.e. when no other commands are running that require it.
	SetDefaultCommand(new ShooterControl());
}

double WhipperSnapper::ReturnPIDInput()
{
	return this->GetAngle();
}

void WhipperSnapper::UsePIDOutput(double input)
{
	this->SetMotorSpeed(input);
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

// Must be called on robot startup so encoder starts tracking. Will initialize to 0.
void WhipperSnapper::EncoderStart()
{
	shooter_encoder->Start();
}

// Reset encoder to 0
void WhipperSnapper::EncoderReset()
{
	shooter_encoder->Reset();
}

double WhipperSnapper::EncoderGetRate(void)
{
	return shooter_encoder->GetRate();
}

double WhipperSnapper::GetAngle(void)
{
	return shooter_encoder->GetAngle();
}

void WhipperSnapper::CheckZeroAndReset(void)
{
	if (shooter_photoeye->Get() > 0)
	{
		this->EncoderReset();
	}
}

