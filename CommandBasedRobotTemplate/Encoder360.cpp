#include "Encoder360.h"
#include <math.h>

Encoder360::Encoder360(uint32_t aChannel, uint32_t bChannel, bool reverseDirection, EncodingType encodingType) :
		Encoder::Encoder(aChannel, bChannel, reverseDirection, encodingType)
{
}
Encoder360::Encoder360(uint8_t aModuleNumber, uint32_t aChannel, uint8_t bModuleNumber, uint32_t _bChannel, bool reverseDirection, EncodingType encodingType) :
		Encoder::Encoder(aModuleNumber, aChannel, bModuleNumber, _bChannel, reverseDirection, encodingType)
{
}
Encoder360::Encoder360(DigitalSource *aSource, DigitalSource *bSource, bool reverseDirection, EncodingType encodingType) :
		Encoder::Encoder(*aSource, *bSource, reverseDirection, encodingType)
{
}
Encoder360::Encoder360(DigitalSource &aSource, DigitalSource &bSource, bool reverseDirection, EncodingType encodingType) :
		Encoder::Encoder(&aSource, &bSource, reverseDirection, encodingType)
{
}


double Encoder360::GetAngle(){
	double distance = this->GetDistance();
	double rawAngle = fmod(distance * 360, 360.0);
	return rawAngle >= 0 ? rawAngle : 360 + rawAngle;
}

double Encoder360::PIDGet()
{
	return this->GetAngle();
}
