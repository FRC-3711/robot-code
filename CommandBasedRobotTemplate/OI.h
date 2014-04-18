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
	float getDriveFwdStick();
	float getDriveStrafeStick();
	float getDriveRotationStick();
	bool checkShooterTrigger();
	float getShooterMotorSpeed();
	float getAxis(uint32_t axis);
	float getShooterMoveRate();
	bool checkShooterCalibrateForward();
	bool checkShooterCalibrateReverse();
	bool checkShooterCalibrateEnable();
	bool checkLoaderLoadButton();
	bool checkLoaderReverseButton();
	bool checkShooterZeroButton();
};

#endif
