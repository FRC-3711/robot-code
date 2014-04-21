#include "ShooterControl.h"
#include <math.h>

static bool Adjusting = false;
static bool AngleControl = false;
static double DesiredAngle = 0.0;

ShooterControl::ShooterControl()
{
	// Use requires() here to declare subsystem dependencies
	Requires(launcher);
}

// Called just before this Command runs the first time
void ShooterControl::Initialize()
{
}

// Called repeatedly when this Command is scheduled to run
void ShooterControl::Execute()
{
	DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();

	launcher->CheckZeroAndReset();
	//Get sensor readings
	double shooterAngle;
	shooterAngle = launcher->GetAngle();
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
	
	// Update the LCD incase anything changed
	dsLCD->UpdateLCD();
}

// Make this return true when this Command no longer needs to run execute()
bool ShooterControl::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ShooterControl::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterControl::Interrupted() {
}

void ShooterControl::CalibrateShooterTalons()
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

void ShooterControl::ReturnToAngle(double currentAngle, bool forwardOnly){
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

void ShooterControl::AdjustShooter(float shooterMove)
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
