#ifndef CLIMBER_H
#define CLIMBER_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author Patrick
 */
class Climber: public Subsystem
{
	private:
		// It's desirable that everything possible under private except
		// for methods that implement subsystem capabilities
		Talon *climber_motor_1;
		Talon *climber_motor_2;
		DigitalInput *switch_climb;
		
	public:
		Climber();
		void InitDefaultCommand();
		void setClimbRate(float climb_rate);
};

#endif
