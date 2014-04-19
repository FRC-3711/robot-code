#ifndef SAMPLESENSORS_H
#define SAMPLESENSORS_H

#include "../CommandBase.h"

/**
 *
 *
 * @author Patrick
 */
class SampleSensors: public CommandBase {
public:
	SampleSensors();
	virtual void Initialize();
	virtual void ResetHeading();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
