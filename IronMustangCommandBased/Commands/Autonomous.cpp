#include "Autonomous.h"
#include "WPILib.h"
#include "Vision/RGBImage.h"
#include "Vision/BinaryImage.h"

// timing is based on the fact that the autonomous loop is called ever 20 miliseconds

#define LIFTER_RAISE_RATE 		-0.55	// the speed at which the lifter is loweredto the lower limit switch during autonomous mode
#define LIFTER_LOWER_RATE		0.55	// the speed to raise the lifter motor
#define FIRE_TIME 				20	 //was 10gfswwew d4bhg	// the number of loop iterations to wait for fire enable
#define SHOT_TIME				60		// the number of loop iterations to wait between shots
#define LIFTER_LOWER_TIME		200		// the number of loop iterations to wait while lowering
#define SHOOTER_MOTOR_SPEED		-0.9	// the speed to run the shooter motor




// global variables, static means they retain their value between loops
static bool position_initialized = FALSE;
static bool lifter_initialized = FALSE; 
static bool first_shot = FALSE;
static bool second_shot = FALSE;
static bool third_shot = FALSE;
static bool fourth_shot = FALSE;
static bool fifth_shot = FALSE;
static bool sixth_shot = FALSE;
static unsigned int lower_lifter_loop = LIFTER_LOWER_TIME;
static unsigned int shot_timer = SHOT_TIME;
static unsigned int fire_timer = FIRE_TIME;



/* Strategy for Autonomous Mode
 * 
 * We don't have any sensors on our robot that will allow us to run feedback loops, so instead of
 * driving from behind the pyramid, turning and firing at the small target, the robot will be touching
 * the back of the pyramid but aimed at the middle target. The lifter will raise until the upper limit
 * switch engages and then it will lower for a short amount of time. When autonomous is engaged, the comp
 * will charge up. Later on the motors will spin up to a preset speed and will fire 3 shots after a short
 * delay
 */

/* Timing
 * 
 * Upon auto mode: Compressor
 * 
 * Raise thingy until switch engages
 * 
 * start timer at that point
 */




Autonomous::Autonomous()
{
	// Use requires() here to declare subsystem dependencies
	Requires(launcher);
}

// Called just before this Command runs the first time
void Autonomous::Initialize()
{	
	// Print some messages to the driverstation LCD
	DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();	
	dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Autonomous Mode On   ");
	dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Hope we're lucky!    ");
	dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "                     ");
	dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "                     ");
	dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "                     ");
	dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "                     ");
	dsLCD->UpdateLCD();
	
	// See if the position of the lifting mechanism is initialized (upper limit tripped)
	if (launcher->getSwitchHigh())
	{
		// position is initialized
		position_initialized = true;
		
		// start the shooter motor
		launcher->setShooterMotorSpeed(SHOOTER_MOTOR_SPEED);
	}
	else
	{
		// position isn't initialized
		position_initialized = false;

	}
}

// Called repeatedly when this Command is scheduled to run
void Autonomous::Execute()
{
	// grab a pointer to the LCD since we'll be sending messages
	DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();	

	// check to see if the lifter poisition has been initialized, but only if it hasn't been initalized already
	if (!position_initialized)
	{
		// if the upper limit switch has been reached, then initailize the position 
		if (launcher->getSwitchHigh())
		{
			position_initialized = true;
			
			// don't forget to stop the motor
			launcher->setElevationRate(0);
			
			// start the shooter motor
			launcher->setShooterMotorSpeed(SHOOTER_MOTOR_SPEED);
		}
		// the upper limit switch hasn't been reached yet, keep driving up there
		else
		{
			// drive lifting mechanism up
			launcher->setElevationRate(LIFTER_RAISE_RATE);
		}
	}
	else
	{
		if (!lifter_initialized)
		{
			if (lower_lifter_loop > 0)
			{
				// lower the motor into position
				launcher->setElevationRate(LIFTER_LOWER_RATE);
				
				// decrement the lifter loop
				lower_lifter_loop--;
			}
			else
			{
				// stop the motor now that the lifter is ready
				launcher->setElevationRate(0);
				
				// decrement the lifter loop
				lifter_initialized = TRUE;
				
				// reset the countdown to fire the first shot
				shot_timer = SHOT_TIME;
				fire_timer = FIRE_TIME;
			}
		}
		else if (!first_shot)
		{
			if (!shot_timer)
			{
				// engage the fire lever
				launcher->fire(TRUE);
				launcher->openShotGate();
				
				if (!fire_timer)
				{
					launcher->closeShotGate();
					// disable the fire lever
					launcher->fire(FALSE);

					// reset the countdown to fire the first shot
					shot_timer = SHOT_TIME;
					fire_timer = FIRE_TIME;
					
					// flag first shot done
					first_shot = true;

					// tell the drivers first shot was fired
					dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Fire 1               ");
					dsLCD->UpdateLCD();
				}
				
				if (fire_timer > 0)
					fire_timer--;
			}
			
			if (shot_timer > 0)
				shot_timer--;
		}
		else if (!second_shot)
		{
			if (!shot_timer)
			{
				// engage the fire lever
				launcher->fire(TRUE);
				launcher->openShotGate();
				
				if (!fire_timer)
				{
					launcher->closeShotGate();
					// disable the fire lever
					launcher->fire(FALSE);

					// reset the countdown to fire the first shot
					shot_timer = SHOT_TIME;
					fire_timer = FIRE_TIME;
					
					// flag first shot done
					second_shot = true;

					// tell the drivers first shot was fired
					dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Fire 2               ");
					dsLCD->UpdateLCD();
				}
				
				if (fire_timer > 0)
					fire_timer--;
			}
			
			if (shot_timer > 0)
				shot_timer--;			
		}
		else if (!third_shot)
		{
			if (!shot_timer)
			{
				// engage the fire lever
				launcher->fire(TRUE);
				launcher->openShotGate();
				
				if (!fire_timer)
				{
					launcher->closeShotGate();
					// disable the fire lever
					launcher->fire(FALSE);

					// reset the countdown to fire the first shot
					shot_timer = SHOT_TIME;
					fire_timer = FIRE_TIME;
					
					// flag first shot done
					third_shot = true;

					// tell the drivers first shot was fired
					dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Fire 3               ");
					dsLCD->UpdateLCD();
				}
				
				if (fire_timer > 0)
					fire_timer--;
			}
			
			if (shot_timer > 0)
				shot_timer--;			
		}
		else if (!fourth_shot)
		{
			if (!shot_timer)
			{
				// engage the fire lever
				launcher->fire(TRUE);
				launcher->openShotGate();
				
				if (!fire_timer)
				{
					launcher->closeShotGate();
					// disable the fire lever
					launcher->fire(FALSE);

					// reset the countdown to fire the first shot
					shot_timer = SHOT_TIME;
					fire_timer = FIRE_TIME;
					
					// flag first shot done
					fourth_shot = true;

					// tell the drivers first shot was fired
					dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Fire 4               ");
					dsLCD->UpdateLCD();
				}
				
				if (fire_timer > 0)
					fire_timer--;
			}
			
			if (shot_timer > 0)
				shot_timer--;			
		}
		else if (!fifth_shot)
		{
			if (!shot_timer)
			{
				// engage the fire lever
				launcher->fire(TRUE);
				launcher->openShotGate();
				
				if (!fire_timer)
				{
					launcher->closeShotGate();
					// disable the fire lever
					launcher->fire(FALSE);

					// reset the countdown to fire the first shot
					shot_timer = SHOT_TIME;
					fire_timer = FIRE_TIME;
					
					// flag first shot done
					fifth_shot = true;

					// tell the drivers first shot was fired
					dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Fire 5               ");
					dsLCD->UpdateLCD();
				}
				
				if (fire_timer > 0)
					fire_timer--;
			}
			
			if (shot_timer > 0)
				shot_timer--;			
		}
		else if (!sixth_shot)
		{
			if (!shot_timer)
			{
				// engage the fire lever
				launcher->fire(TRUE);
				launcher->openShotGate();
				
				if (!fire_timer)
				{
					launcher->closeShotGate();
					// disable the fire lever
					launcher->fire(FALSE);

					// reset the countdown to fire the first shot
					shot_timer = SHOT_TIME;
					fire_timer = FIRE_TIME;
					
					// flag first shot done
					sixth_shot = true;

					// tell the drivers first shot was fired
					dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Fire 6               ");
					dsLCD->UpdateLCD();

					// reset variables
//					position_initialized = FALSE;
//					lifter_initialized = FALSE; 
//					first_shot = FALSE;
//					second_shot = FALSE;
//					third_shot = FALSE;
//					lower_lifter_loop = LIFTER_LOWER_TIME;
//					shot_timer = SHOT_TIME;
//					fire_timer = FIRE_TIME;
					
					// stop firing, just in case
					launcher->fire(FALSE);
					
					// stop the shooter motor since teleop starts with the motor off
					launcher->setShooterMotorSpeed(0);
				}
				
				if (fire_timer > 0)
					fire_timer--;
			}
			
			if (shot_timer > 0)
				shot_timer--;			
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool Autonomous::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void Autonomous::End() 
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Autonomous::Interrupted() {
}

