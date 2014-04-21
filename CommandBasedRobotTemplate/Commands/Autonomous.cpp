#include "Autonomous.h"
#include "WPILib.h"
#include "ShooterControl.h"
#include "Drive.h"
#include <math.h>

// timing is based on the fact that the autonomous loop is called every 20 miliseconds
// global variables, static means they retain their value between loops

static int STEP;

//static float CUR_DIST_TO_GOAL = 1000.0;
//static float PERFECT_SHOT_DISTANCE = 100.0;
static int MOVE_COUNTER = 75;
static float PERFECT_SHOT_ANGLE = 350.0;
static float PERFECT_SHOT_SPEED = 1.0;
static int WAIT_TO_SHOOT = 25;
static bool SHOOT = false;

#define MOTOR_TIME_ON 15
static bool Shooting = false;
static int MoveCounter = 0;
static int WaitToShoot = 0;
static double DesiredAngle = 0.0;
static int MotorTimer = 0;

Autonomous::Autonomous()
{
	// Use requires() here to declare subsystem dependencies
	Requires(launcher);
	Requires(chassis);
	Requires(sensors);
}

// Called just before this Command runs the first time
void Autonomous::Initialize()
{	
	// Print some messages to the driverstation LCD
	DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();	
	dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "                     ");
	dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "                     ");
	dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "                     ");
	dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "                     ");
	dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "                     ");
	dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "                     ");
	dsLCD->UpdateLCD();
	STEP = 0;
	DesiredAngle = 0.0;
	MoveCounter = MOVE_COUNTER;
	// See if the position of the lifting mechanism is initialized (upper limit tripped)
}

// Called repeatedly when this Command is scheduled to run
void Autonomous::Execute()
{
	// grab a pointer to the LCD since we'll be sending messages
	DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();	

	// DistanceSensor check distance to goal
	// If distance to the goal = the desired distance, if not move forward/back accordingly
	// if the facing goal is hot, shoot
	// if not wait 5 seconds, then shoot
	launcher->CheckZeroAndReset();
	float CUR_ANGLE = launcher->GetAngle();
	dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "STEP=%d                 ", STEP);
	dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "CUR_ANGLE=%1.1f         ", CUR_ANGLE);
	dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "DESIRED_ANGLE=%1.1f     ", DesiredAngle);
	switch(STEP){
	case 0: //Init MoveCounter
		MoveCounter = MOVE_COUNTER;
		STEP++;
		break;
	case 1: //START - MOVE TO THE PERFECT POSITION
		if(MoveCounter <= 0){
			// Stop driving
			chassis->mecanumDrive(0.0, 0.0, 0.0, 0.0);
			WaitToShoot = WAIT_TO_SHOOT;
			STEP++;
		}else{
			// Go forward
			chassis->mecanumDrive(0.0, -0.5, 0.0, 0.0);
			MoveCounter--;
		}
		break;
	case 2:
		// Move shooter forward first, to knock down the catcher
		DesiredAngle = 10.0;
		dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Move shooter forward");
		if(ReturnToAngle(CUR_ANGLE, 0.4, false)){STEP++;}
		break;		
		
	case 3:
		// Move shooter arm back
		DesiredAngle = 330.0;
		dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Move shooter back   ");
		if(ReturnToAngle(CUR_ANGLE, 0, false)){STEP++;}
		break;
		
	case 4:
		// Zero it up
		DesiredAngle = 0.0;
		dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Move shooter zero   ");
		if(ReturnToAngle(CUR_ANGLE, 0, false)){STEP++;}
		break;
	case 5: // Get hot goal to determine which side to move to
		if (WaitToShoot >= 0)
		{
			WaitToShoot--;
		}
		else {
			STEP++;
		}
		break;
	case 6: // SET ARM TO PERFECT ANGLE
		DesiredAngle = PERFECT_SHOT_ANGLE;
		dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Move shooter PERF   ");
		if(ReturnToAngle(CUR_ANGLE, 0, false)){STEP++;}	
		break;
	case 7: // Shoot
		if (SHOOT) {
			MotorTimer = MOTOR_TIME_ON;
			Fire(PERFECT_SHOT_SPEED);
		}
		STEP++;
		break;
	case 8: //Finish the shot
		if (SHOOT) {
			Fire(PERFECT_SHOT_SPEED);
		}
		break;
	}
	dsLCD->UpdateLCD();
}

// Make this return true when this Command no longer needs to run execute()
bool Autonomous::IsFinished() {
	//STEP = 0;
	return false;
	
}

// Called once after isFinished returns true
void Autonomous::End() 
{
	//STEP = 0;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Autonomous::Interrupted() {
	//STEP = 0;
}

bool Autonomous::ReturnToAngle(double currentAngle, float speed, bool forwardOnly){
	double error = DesiredAngle - currentAngle;
	double errorFactor = 0.0;
	if (error >= 2.0 || error <= -2.0)
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
		if(speed == 0){
		errorFactor = (error / 180) * 0.5;
		if (error > 0) {errorFactor += 0.1;}
		else if (error < 0){errorFactor -= 0.1;}
			launcher->SetMotorSpeed(errorFactor);
		}else{
			launcher->SetMotorSpeed(speed);
		}
		return false;
	
	}
	else
	{
		launcher->MotorOff();
		return true;
	}
}

void Autonomous::Fire(float shooterSpeed)
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
