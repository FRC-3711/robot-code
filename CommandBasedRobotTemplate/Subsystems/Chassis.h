#ifndef CHASSIS_H
#define CHASSIS_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author Patrick
 */
class Chassis: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	RobotDrive *drive;
public:
	Chassis();
	void InitDefaultCommand();
	void mecanumDrive(float x, float y, float z, float headingAngle);
//	void tankDrive(double left, double right);
//	void arcadeDrive(Joystick *stick);
};

#endif
