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
	
	shooterEncoder = new Encoder(SHOOTER_ENCODER_CHA, SHOOTER_ENCODER_CHB, true);
	shooterEncoder->SetDistancePerPulse(12.0 / 45.0 / 360.0); // 360 pulses per axle rotation; 45:12 reduction to arm
	shooterEncoder->SetMinRate(1.0); //arbitrary; sets lowest threshold of pulses/s before encoder shows "stopped"
	shooterEncoder->Start();
	
	
	
	photoEye = new DigitalInput(SHOOTER_PHOTOEYE);
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

void Sensors::ShooterEncoderStart()
{
	shooterEncoder->Start();
}

void Sensors::ShooterEncoderReset()
{
	shooterEncoder->Reset();
}

double Sensors::ShooterEncoderGetRate(void)
{
	return shooterEncoder->GetRate();
}

double Sensors::ShooterGetAngle(void)
{
	double shooterDistance = this->ShooterEncoderGetDistance();
	double rawAngle = fmod(shooterDistance * 360, 360.0);
	return rawAngle >= 0 ? rawAngle : 360 + rawAngle;
}

double Sensors::ShooterEncoderGetDistance(void)
{
	return shooterEncoder->GetDistance();
}

int32_t Sensors::ShooterEncoderGetRaw(void)
{
	return shooterEncoder->GetRaw();
}

void Sensors::ShooterCheckZeroAndReset(void)
{
	if (photoEye->Get() > 0)
	{
		this->ShooterEncoderReset();
	}
}

float Sensors::DistanceSensorGetDistance(void){
	return distanceSensor->GetVoltage() * DISTANCE_SENSOR_SENSITIVITY;
	//outputs inches (Hopefully)
}
