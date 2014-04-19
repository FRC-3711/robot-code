#ifndef TIME_H
#define TIME_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

class Time: public Subsystem
{

private:
	Timer *timecount;

public:
	Time();
	void InitDefaultCommand();
	void StartTimer();
	double GetTimeCount();
};

#endif
