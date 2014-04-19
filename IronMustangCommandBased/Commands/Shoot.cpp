#include "Shoot.h"

//thje amount of time to keep the gate open in number * 20ms
#define GATE_TIME 20

// Declare a global variable that determines when the shooter motor is enable
static bool ShooterMotorEnabled = FALSE;
static bool LimitSwitchHigh = FALSE;
static bool LimitSwitchLow = FALSE;
static bool StickIsClimbMode = FALSE;
static bool GateOpen = FALSE;
static float LiftRate;
static float ShootRate;
static unsigned int GateOpenTimer = 100;

Shoot::Shoot()
{
	// Use requires() here to declare subsystem dependencies
	Requires(launcher);
}

// Called just before this Command runs the first time
void Shoot::Initialize()
{
	DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();
	dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "Teleop Mode On       ");
	dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Go forth and dominate");
	dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "                     ");
	dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "                     ");
	dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "                     ");
	dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "                     ");	
	dsLCD->UpdateLCD();
	
}

// Called repeatedly when this Command is scheduled to run
void Shoot::Execute()
{
	DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();
	
	// check if the climber button has changed status
	if (oi->checkClimberButton())
	{
		// flag the status
		StickIsClimbMode = true;
		
		// disable the lifter motor
		launcher->setElevationRate(0);
		
		// alert the drivers
		dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Shooter Stick: Climb ");
	}
	else
	{
		// flag the status
		StickIsClimbMode = false;
		
		// alert the drivers
		dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Shooter Stick: Aim   ");
	}
			
	// Capture shoooter motor speed
	ShootRate = oi->getShooterMotorSpeed();
//	ShootRate *= -1;
	
	// Check if the shooter motor enable/disable status has changed
	if(oi->checkShooterMotorDisable())
	{
		// change the state flag
		ShooterMotorEnabled = FALSE;

		// disable the motor
		launcher->disableShooterMotor();

		// alert the drivers of this status
		dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Shoot Mtr: Off            ");	
//		dsLCD->UpdateLCD();
	}
	else if(oi->checkShooterMotorEnable())
	{
		// change the state flag
		ShooterMotorEnabled = TRUE;

		// alert the drivers of this status
//		dsLCD->Printf(DriverStationLCD::kUser_Line1, 11, "Time: %4.1f", GetClock());

		dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Shoot Mtr Spd: %1.3f    ", ShootRate);	
//		dsLCD->UpdateLCD();
	}

	// If enabled, map the motor speed to the motor speed control on the joystick
	if (ShooterMotorEnabled)
	{
//		launcher->setShooterMotorSpeed(oi->getShooterMotorSpeed());
		launcher->setShooterMotorSpeed(ShootRate);
	}
	
	// See if the trigger has been pulled and launch a frisbee if so
	// only allow this to happen if the shooter motor is enabled
	if (oi->checkShooterTrigger() && ShooterMotorEnabled)
	{
		launcher->fire(TRUE);
		
		// start the feed mechanism
		launcher->openShotGate();

		if (!GateOpen)
		{
			// start a timer to wait until the servo is ready to close again
			GateOpenTimer = GATE_TIME;
		}
		
		GateOpen = true;
	}
	else
	{
		launcher->fire(FALSE);
	}
	
	// if GateOpen is active, count down the time to close the servo
	if (GateOpen)
	{
		if (GateOpenTimer > 0)
		{
			launcher->openShotGate();
			GateOpenTimer--;
		}
		else
		{
			//close the gate
			launcher->closeShotGate();
			GateOpen = false;	
		}
	}
	
	
	// Manipulate the lift mechanism if the stick is in lifter mode
	if (!StickIsClimbMode)
	{
		// check to see if a limit switch has fired, reset the switch if necesssary
		if (launcher->getSwitchHigh())
		{
			LimitSwitchHigh = TRUE;
			dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "Limit High: On ");
	//		dsLCD->UpdateLCD();
		}
		else
		{
			LimitSwitchHigh = FALSE;
			dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "Limit High: Off");
//			dsLCD->UpdateLCD();
		}
		if (launcher->getSwitchLow())
		{
			LimitSwitchLow = TRUE;
			dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "Limit Low: On ");
	//		dsLCD->UpdateLCD();
		}
		else
		{
			LimitSwitchLow = FALSE;
			dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "Limit Low: Off");
	//		dsLCD->UpdateLCD();
		}
		// capture joystick lift rate
		LiftRate = oi->getShooterLiftRate();
	
		// stop the motor if a switch is fired and we're moving in the direction of the switch
		if (LimitSwitchHigh && (LiftRate < 0))
		{
			// stop the motor immeidately!!!!
			launcher->setElevationRate(0);
		}
		else if (LimitSwitchLow && (LiftRate > 0))
		{
			// stop the motor immeidately!!!!
			launcher->setElevationRate(0);
		}
		// all the motor to move even if the switches are on, in the direction opposite the fired switch
		else if (LimitSwitchHigh && (LiftRate > 0))
		{
			// allow the tilt assembly to move away from the switch
			launcher->setElevationRate(LiftRate);
		}
		else if (LimitSwitchLow && (LiftRate < 0))
		{
			// allow the tilt assembly to move away from the switch
			launcher->setElevationRate(LiftRate);
		}
		else
		{
			// allow the tilt assembly to move either direction since no switches are fired
			launcher->setElevationRate(LiftRate);
		}
	}

	// Update the LCD incase anything changed
	dsLCD->UpdateLCD();
	
	// decrement timers
	
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
