#ifndef FRISBEELAUNCHER_H
#define FRISBEELAUNCHER_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class FrisbeeLauncher: public Subsystem 
{

private:
	Talon *shooter_motor_1;
	Talon *shooter_motor_2;
	Victor *tilt_motor;
	Compressor *compressor;
	Solenoid *solenoid;
	DigitalInput *switch_high;
	DigitalInput *switch_low;
	Servo *shot_gate;

public:
	FrisbeeLauncher();
	void InitDefaultCommand();
	void disableShooterMotor(void);
	void setShooterMotorSpeed(float speed);
	void fire(bool fire);
	void setElevationRate(float lift_rate);
	bool getSwitchHigh(void);
	bool getSwitchLow(void);
	void openShotGate(void);
	void closeShotGate(void);
};

#endif
