#include "Time.h"
#include "../Robotmap.h"
#include "../Commands/Autonomous.h"

// The plan with this subsystem is to create an instance of Timer() and use it to measure timing of command
// calls. There will probably be more uses for this in the future
Time::Time() : Subsystem("Time")
{
	timecount = new Timer();
}

// Use this in the Autonomous Command
void Time::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	SetDefaultCommand(new Autonomous());
}

void Time::StartTimer()
{
	timecount->Start();
}

double Time::GetTimeCount()
{
	return timecount->Get();
}
