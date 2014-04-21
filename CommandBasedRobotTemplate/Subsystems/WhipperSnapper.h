#ifndef WhipperSnapper_H
#define WhipperSnapper_H
#include "Commands/Subsystem.h"
#include "../Encoder360.h"
#include "WPILib.h"

class WhipperSnapper: public PIDSubsystem 
{

private:
	Talon *shooter_motor_1;
	Talon *loader_motor;
	Encoder360 *shooter_encoder;
	DigitalInput *shooter_photoeye;

public:
	WhipperSnapper();
	void InitDefaultCommand();
	void SetMotorSpeed(float speed);
	void MotorOff();
	void StartLoader(void);
	void ReverseLoader(void);
	void StopLoader(void);
	void EncoderStart(void);
	void EncoderReset(void);
	double EncoderGetRate(void);
	double GetAngle(void);
	double ReturnPIDInput(void);
	void UsePIDOutput(double);
	void CheckZeroAndReset(void);

};

#endif
