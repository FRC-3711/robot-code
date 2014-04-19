#include "Shoot.h"
#include <math.h>

//the amount of time to run the firing motors in number * 20ms
#define MOTOR_TIME_ON 15
static bool Shooting = false;
static bool Adjusting = false;
static bool AngleControl = false;
static double DesiredAngle = 0.0;
static int MotorTimer = 0;

Shoot::Shoot()
{
	// Use requires() here to declare subsystem dependencies
	Requires(launcher);
}

// Called just before this Command runs the first time
void Shoot::Initialize()
{
	launcher->EncoderReset();
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute()
{
	DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();

	launcher->CheckZeroAndReset();
	//Get sensor readings
	float shooterSpeed;
	shooterSpeed = oi->getShooterMotorSpeed();
	dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "%1.4f", shooterSpeed);
	double shooterAngle;
	shooterAngle = launcher->GetAngle();
//	SmartDashboard::PutNumber("Shooter Angle", shooterAngle);
//	SmartDashboard::PutNumber("Shooter Speed", shooterSpeed);
	dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "%1.4f", shooterAngle);
		
	//User inputs
	if (oi->checkShooterCalibrateEnable())
	{
		CalibrateShooterTalons();
	}
		
	if (oi->checkLoaderLoadButton())
	{
		dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Loader On     ");
		launcher->StartLoader();
	}
	else if (oi->checkLoaderReverseButton())
	{
		dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Loader Reverse");
		launcher->ReverseLoader();
	}
	else
	{
		dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Loader Off    ");
		launcher->StopLoader();
	}
	
	float shooterMove = oi->getShooterMoveRate();
	dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "%1.4f", shooterMove);
	this->AdjustShooter(shooterMove);
	
	if (oi->checkShooterTrigger())
	{
		Shooting = true;
		MotorTimer = MOTOR_TIME_ON;
	}
	if (Shooting)
	{
		this->Fire(shooterSpeed);
	}
	
	// Update the LCD incase anything changed
	dsLCD->UpdateLCD();
}

// Make this return true when this Command no longer needs to run execute()
bool Shoot::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void Shoot::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Shoot::Interrupted() {
}

void Shoot::CalibrateShooterTalons()
{
	if (oi->checkShooterCalibrateForward())
	{
		launcher->SetMotorSpeed(1.0);
	}
	else if (oi->checkShooterCalibrateReverse())
	{
		launcher->SetMotorSpeed(-1.0);
	}
	else (launcher->MotorOff());
}

void Shoot::ReturnToAngle(double currentAngle, bool forwardOnly){
	double error = DesiredAngle - currentAngle;
	double errorFactor;
	if (error >= 5.0 || error <= -5.0)
	{
		if (forwardOnly)
		{
			if (error < 0.0)
			{
				error = 360.0 + error;
			}
			if (error > 180.0)
			{
				error = 180.0; // we can play with this value because we'll recalculate it in 20ms anyway
			}
		}
		else
		{
			if (error > 180.0)
			{
				error -= 360.0;
			}
			else if (error < -180.0)
			{
				error += 360.0;
			}
		}
		errorFactor = (error / 180) * 0.6;
		launcher->SetMotorSpeed(errorFactor);
	}
	else
	{
		AngleControl = false;
	}
}

void Shoot::AdjustShooter(float shooterMove)
{
	if ((shooterMove > 0.1) || (shooterMove < -0.1))
	{
		launcher->SetMotorSpeed(pow(shooterMove, 5) * -0.5);
		Adjusting = true;
	}
	else if (Adjusting)
	{
		launcher->MotorOff();
		Adjusting = false;
	}
}

void Shoot::Fire(float shooterSpeed)
{
	if (MotorTimer > 0)
	{
		launcher->SetMotorSpeed(shooterSpeed);
		MotorTimer--;
	}
	else if (MotorTimer <= 0)
	{
		launcher->MotorOff();
		Shooting = false;
	}
}
