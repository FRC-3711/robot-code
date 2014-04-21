#include "Fire.h"

#define MOTOR_TIME_ON 15
static int MotorTimer = 0;

Fire::Fire()
{
	// will override any other commands requiring launcher (i.e. Shoot, the launcher default command)
	Requires(launcher);
}

void Fire::Initialize()
{
	MotorTimer = MOTOR_TIME_ON;
}

void Fire::Execute()
{
	float shooterSpeed;
	shooterSpeed = oi->getShooterMotorSpeed();

	launcher->SetMotorSpeed(shooterSpeed);
	MotorTimer--;
}

bool Fire::IsFinished()
{
	return MotorTimer <= 0;
}

void Fire::Interrupted()
{
}

void Fire::End()
{
	launcher->MotorOff();
}
