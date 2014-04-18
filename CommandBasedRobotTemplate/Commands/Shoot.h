#ifndef SHOOT_H
#define SHOOT_H

#include "../CommandBase.h"

class Shoot: public CommandBase {
public:
	Shoot();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	bool Autonomous;
private:
	void CalibrateShooterTalons();
	void ReturnToAngle(double currentAngle, bool forwardOnly);
	void ReturnToZero(double angle);
	void AdjustShooter(float shooterMove);
	void Fire(float shooterSpeed);
};

#endif
