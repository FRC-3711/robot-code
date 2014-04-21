#ifndef SHOOTERCONTROL_H
#define SHOOTERCONTROL_H

#include "../CommandBase.h"

class ShooterControl: public CommandBase {
public:
	ShooterControl();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
private:
	void CalibrateShooterTalons();
	void ReturnToAngle(double currentAngle, bool forwardOnly);
	void ReturnToZero(double angle);
	void AdjustShooter(float shooterMove);
	void Fire(float shooterSpeed);
};

#endif
