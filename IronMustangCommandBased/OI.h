#ifndef OI_H
#define OI_H

#include "WPILib.h"

class OI {
private:
//	static const int JOYSTICK_PORT = 1;
	
	Joystick *driver_stick;
	Joystick *shooter_stick;
	
public:
	OI();
	Joystick *getJoystick();
	float getDriverLeftStick();
	float getDriverRightStick();
	bool checkShooterMotorEnable();
	bool checkShooterMotorDisable();
	bool checkShooterTrigger();
	float getShooterMotorSpeed();
	float getShooterLiftRate();
	bool checkClimberButton();
};

#endif
