#ifndef ENCODER360_H
#define ENCODER360_H
#include "WPILib.h"

class Encoder360 : public Encoder {
	
public:
	Encoder360(uint32_t aChannel, uint32_t bChannel, bool reverseDirection=false, EncodingType encodingType = k4X);
	Encoder360(uint8_t aModuleNumber, uint32_t aChannel, uint8_t bModuleNumber, uint32_t _bChannel, bool reverseDirection=false, EncodingType encodingType = k4X);
	Encoder360(DigitalSource *aSource, DigitalSource *bSource, bool reverseDirection=false, EncodingType encodingType = k4X);
	Encoder360(DigitalSource &aSource, DigitalSource &bSource, bool reverseDirection=false, EncodingType encodingType = k4X);
	double Encoder360::GetAngle(void);
	double Encoder360::PIDGet();
};

#endif
