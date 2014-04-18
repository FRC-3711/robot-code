#include "CommandBase.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/FrisbeeLauncher.h"
#include "Subsystems/Climber.h"
#include "Subsystems/Time.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

// Initialize a single static instance of all of your subsystems to NULL
OI* CommandBase::oi = NULL;
Chassis* CommandBase::chassis = NULL;
FrisbeeLauncher* CommandBase::launcher = NULL;
Climber* CommandBase::climber = NULL;
Time* CommandBase::robot_timer = NULL;

void CommandBase::init()
{
    // Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	chassis = new Chassis();
	launcher = new FrisbeeLauncher();
	climber = new Climber();
	oi = new OI();
	robot_timer = new Time();
}
