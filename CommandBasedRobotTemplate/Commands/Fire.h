#ifndef FIRE_H
#define FIRE_H

#include "../CommandBase.h"

class Fire : public CommandBase {
public:
	Fire();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void Interrupted();
	virtual void End();
};

#endif
