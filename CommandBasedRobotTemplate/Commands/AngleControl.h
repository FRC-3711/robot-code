#ifndef ANGLECONTROL_H
#define ANGLECONTROL_H

#include "../CommandBase.h"

class AngleControl : public CommandBase {
public:
	AngleControl(double angle);
	void Initialize();
	void Execute();
	bool IsFinished();
	void Interrupted();
	void End();
};

#endif
