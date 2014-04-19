#ifndef CLIMB_H
#define CLIMB_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Patrick
 */
class Climb: public CommandBase {
public:
	Climb();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
