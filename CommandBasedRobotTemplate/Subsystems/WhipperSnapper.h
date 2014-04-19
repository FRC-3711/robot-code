#ifndef WhipperSnapper_H
#define WhipperSnapper_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class WhipperSnapper: public Subsystem 
{

private:
	Talon *shooter_motor_1;
	Talon *loader_motor;

public:
	WhipperSnapper();
	void InitDefaultCommand();
	void SetMotorSpeed(float speed);
	void MotorOff();
	void StartLoader(void);
	void ReverseLoader(void);
	void StopLoader(void);
};

#endif
