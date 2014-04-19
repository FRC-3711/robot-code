#ifndef SENSORS_H
#define SENSORS_H
#include <ADXL345_I2C.h>
#include "Commands/Subsystem.h"
#include "WPILib.h"


class Sensors: public Subsystem
{

private:
	ADXL345_I2C *accelerometer;
	Gyro *gyro;
	AnalogChannel *gyroTemp;
	Encoder *shooterEncoder;
	DigitalInput *photoEye;
	AnalogChannel *distanceSensor;
	
public:
	Sensors();
	void InitDefaultCommand();
	double Sensors::AccelerometerSampleX(void);
	double Sensors::AccelerometerSampleY(void);
	double Sensors::AccelerometerSampleZ(void);
	void Sensors::GyroReset(void);
	float Sensors::GyroGetAngle(void);
	double Sensors::GyroGetRate(void);
	void Sensors::ShooterEncoderStart(void);
	void Sensors::ShooterEncoderReset(void);
	double Sensors::ShooterEncoderGetRate(void);
	double Sensors::ShooterEncoderGetDistance(void);
	double Sensors::ShooterGetAngle(void);
	int32_t Sensors::ShooterEncoderGetRaw(void);
	void Sensors::ShooterCheckZeroAndReset(void);
	float Sensors::DistanceSensorGetDistance(void);
};

#endif
