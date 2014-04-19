#include "Sensors.h"
#include "../Robotmap.h"
#include "../Commands/SampleSensors.h"
#include <ADXL345_I2C.h>
#include <math.h>

Sensors::Sensors() : Subsystem("Sensors")
{
	// Create an instance of each sensor classs
	
	// Create an accelerometer class on the I2C bus of module 1, using a acceleration range of +/- 2G
	accelerometer = new ADXL345_I2C(ACCEL_MODULE, ADXL345_I2C::kRange_2G);
	
	// Create a gyro class for the Analog Devices ADW22307 gyro (2012 kit of parts)
	gyro = new Gyro(1, GYRO_ANALOG_IN);
	
	// Create a t
	gyroTemp = new AnalogChannel(1, GYRO_TEMP_ANALOG_IN);
	
	distanceSensor = new AnalogChannel(DISTANCE_SENSOR_SLOT,DISTANCE_SENSOR_CHANNEL);
}

void Sensors::InitDefaultCommand() 
{
	SetDefaultCommand(new SampleSensors());
}

// Sample and return the value of the accelerometer's X axis (should measure 0G when stationary)
double Sensors::AccelerometerSampleX(void)
{
	return accelerometer->GetAcceleration(ADXL345_I2C::kAxis_X);
}

// Sample and return the value of the accelerometer's Y axis (should measure 0G when stationary)
double Sensors::AccelerometerSampleY(void)
{
	return accelerometer->GetAcceleration(ADXL345_I2C::kAxis_Y);
}

// Sample and return the value of the accelerometer's Z axis (should measure 1G when stationary)
double Sensors::AccelerometerSampleZ(void)
{
	return accelerometer->GetAcceleration(ADXL345_I2C::kAxis_Z);
}

// gyro
void Sensors::GyroReset(void)
{
	gyro->Reset();
	//Gyro *gyroPtr = Gyro::GetInstance();
//	DriverStationLCD *dsLCD = DriverStationLCD::GetInstance();
	//gyro->Reset();
}

float Sensors::GyroGetAngle(void)
{
	return gyro->GetAngle();
}

double Sensors::GyroGetRate(void)
{
	return gyro->GetRate();
}

float Sensors::DistanceSensorGetDistance(void)
{
	//outputs inches (Hopefully)
	return distanceSensor->GetVoltage() * DISTANCE_SENSOR_SENSITIVITY;
}
