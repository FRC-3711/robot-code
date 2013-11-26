#ifndef DRIVEWITHLOGITECHJOYSTICK_H
#define DRIVEWITHLOGITECHJOYSTICK_H

#include "../CommandBase.h"

class Drive: public CommandBase {
public:
	Drive();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
