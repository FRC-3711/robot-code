// This class is used to sample the sensors onboard the robot. Sensors can include any of the following:
//
// Gyros (rate sensors)
// Accelerometers
// Digital compass or magnetometers
// Distance sensors (rangefinders)
// Shaft encoders

#include "SampleSensors.h"
#include <math.h>

static float 	AccelerationX 	= 0.0;
static float 	AccelerationY 	= 0.0;
static float 	AccelerationZ 	= 0.0;
static float 	GyroAngle 		= 0.0;
static float 	GyroRate 		= 0.0;
static double 	EncoderRate		= 0.0;
static double	EncoderDistance	= 0.0;
static double	ShooterAngle 	= 0.0;

SampleSensors::SampleSensors()
{
	// Declare dependancy on the sensor class
	Requires(sensors);
}

// Called just before this Command runs the first time
void SampleSensors::Initialize()
{
	// Initialize the gyro
	sensors->GyroReset();
	sensors->ShooterEncoderReset();
}

// Called just before this Command runs the first time
void SampleSensors::ResetHeading()
{
	// Initialize the gyro
	sensors->GyroReset();
}

// Called repeatedly when this Command is scheduled to run
void SampleSensors::Execute()
{
	DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();
	
	// Sample the accelerometer's three axes and print to the driver station LCD
	AccelerationX = sensors->AccelerometerSampleX();
	AccelerationY = sensors->AccelerometerSampleY();
	AccelerationZ = sensors->AccelerometerSampleZ();
//	dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "AccX: %1.4f Gs      ", AccelerationX);	
//	dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "AccY: %1.4f Gs      ", AccelerationY);	
//	dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "AccZ: %1.4f Gs      ", AccelerationZ);	

	// Sample Gyro Data and output it to the LCD
	GyroAngle = sensors->GyroGetAngle();
	GyroRate = sensors->GyroGetRate();
	
	float distance = sensors->DistanceSensorGetDistance();
	dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Distance: %1.1f", distance);
	
	//if ((Distance < dLow) || (Distance == 0)){dLow=Distance;}
	//dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "D Low: %1.1f in      ", dLow);
	//dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "Rate: %1.1f deg/sec   ", GyroRate);
	
	EncoderDistance = sensors->ShooterEncoderGetDistance();
	EncoderRate = sensors->ShooterEncoderGetRate();
	ShooterAngle = fmod((EncoderDistance * 360), 360);
		
	// Update the Driver Station LCD with the new data aquired from this loop iteration
	dsLCD->UpdateLCD();
}

// Make this return true when this Command no longer needs to run execute()
bool SampleSensors::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void SampleSensors::End() {
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SampleSensors::Interrupted() {
}
