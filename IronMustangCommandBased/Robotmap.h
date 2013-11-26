#ifndef ROBOTMAP_H
#define ROBOTMAP_H


/*
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
 
// PWM Assignments
#define RIGHT_DRIVE_MOTOR	1
#define LEFT_DRIVE_MOTOR	2
#define SHOOTER_MOTOR_1		3
#define SHOOTER_MOTOR_2		4
#define CLIMB_MOTOR_1		5
#define CLIMB_MOTOR_2		6
#define	TILT_MOTOR			7
#define SERVO_MOTOR_1		9

//Relay Assignments
#define COMPRESSOR_RELAY	1

// Digital I/O Assignments
#define	LIMIT_SWITCH_HIGH	1
#define LIMIT_SWITCH_LOW	2
#define COMPRESSOR_SWITCH	3
#define LIMIT_CLIMB			4

// Solenoid Breakout Board Assignments
#define SOLENOID			1

// Joystick Port Assignments
// This is the exact number the joystick must be set to in DriverStation
#define DRIVE_STICK_PORT			1		// Logitech Dual Action
#define SHOOTER_STICK_PORT			2		// Logitech Attack 3
#define CLIMBER_STICK_PORT			3		// Logitech Attack 3

// Joystick Button Assignments

// The Logitech Dual Action has the following mappings
// Joystick Button Number		RawButtonNumber()
//			1						1
//			2						2
//			3						3
//			4						4
//			5						5
//			6						6
//			7						7
//			8						8
//	Upper left of 3-button group	9

// The Logitech Attack 3 Joystick has the following mappings
// Joystick Button Number		RawButtonNumber()
// 		 Trigger					1
//			2						2
//			3						3
//			4						Not Supported
//			5						5
//			6						6
//			7						7
//			10						10
//			11						11
//			+/- dial				Axis3

#define SHOOTER_MOTOR_ENABLE		3
#define SHOOTER_MOTOR_DISABLE		2
#define SHOOTER_TRIGGER				1
#define SHOOTER_SPEED_AXIS			3
#define CLIMBER_BUTTON				7


// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// #define RANGE_FINDER_PORT 1
// #define RANGE_FINDER_MODULE 1

#endif
