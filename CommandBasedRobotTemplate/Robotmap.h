#ifndef ROBOTMAP_H
#define ROBOTMAP_H

/*
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// Raw Joystick Axis Assignments
#define	STICK_FWD_AXIS		2 //y
#define	STICK_STRAFE_AXIS	1 //x
#define STICK_ROTATE_AXIS	3

#define SHOOTER_MOVE_AXIS	2
#define SHOOTER_SPEED_AXIS	3

// PWM Assignments
#define DRIVE_FRONT_LEFT	1
#define DRIVE_FRONT_RIGHT	2
#define DRIVE_BACK_LEFT		3
#define DRIVE_BACK_RIGHT	4
#define SHOOTER_MOTOR_1		5
#define LOADER_MOTOR		7

// Analog Channel Assignments
#define GYRO_ANALOG_IN		1
#define GYRO_TEMP_ANALOG_IN	2
#define DISTANCE_SENSOR_SLOT	1
#define DISTANCE_SENSOR_CHANNEL	3

// Digital I/O Assignments
#define SHOOTER_ENCODER_CHA	1
#define SHOOTER_ENCODER_CHB	2
#define SHOOTER_PHOTOEYE	3

// I2C Bus Assignments
#define ACCEL_MODULE		1

// Joystick Port Assignments
// This is the exact number the joystick must be set to in DriverStation
#define DRIVE_STICK_PORT			1		// Logitech Extreme 3D
#define SHOOTER_STICK_PORT			2		// Logitech Attack 3

// Joystick Button Assignments
#define SHOOTER_TRIGGER				1
#define LOADER_LOAD_BUTTON			2
#define LOADER_REVERSE_BUTTON		3
#define SHOOTER_ZERO_BUTTON			4
#define SHOOTER_SHOT_ANGLE_BUTTON	5
#define CALIBRATE_FORWARD_BUTTON	6
#define CALIBRATE_REVERSE_BUTTON	7
#define CALIBRATE_ENABLE_BUTTON		9

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// #define RANGE_FINDER_PORT 1
// #define RANGE_FINDER_MODULE 1

#define DISTANCE_SENSOR_SENSITIVITY	90
#endif
