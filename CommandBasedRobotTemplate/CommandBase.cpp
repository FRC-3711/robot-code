#include "CommandBase.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/WhipperSnapper.h"
#include "Subsystems/Sensors.h"
#include "Subsystems/Time.h"
#include "Commands/Scheduler.h"
#include <math.h>

CommandBase::CommandBase(const char *name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

// Initialize a single static instance of all of your subsystems to NULL
OI* 				CommandBase::oi 			= NULL;
Chassis* 			CommandBase::chassis 		= NULL;
WhipperSnapper*		CommandBase::launcher		= NULL;
Time* 				CommandBase::robot_timer 	= NULL;
Sensors* 			CommandBase::sensors 		= NULL;
// Declare a global variable that determines when the shooter motor is enable

void CommandBase::init()
{
    // Create a single static instance of all of your subsystems.
	chassis 		= new Chassis();
	launcher 		= new WhipperSnapper();
	oi 				= new OI();
	robot_timer 	= new Time();
	sensors 		= new Sensors();
}
