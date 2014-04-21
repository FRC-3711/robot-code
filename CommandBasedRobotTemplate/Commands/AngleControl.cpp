#include "AngleControl.h"

static double Angle;

AngleControl::AngleControl(double angle)
{
	Requires(launcher);
	Angle = angle;
}

void AngleControl::Initialize()
{
	launcher->SetSetpoint(Angle);
}

void AngleControl::Execute()
{
	launcher->Enable();
}

bool AngleControl::IsFinished()
{
	return launcher->OnTarget();
}

void AngleControl::Interrupted()
{
	launcher->Disable();
}

void AngleControl::End()
{
	launcher->Disable();
}
