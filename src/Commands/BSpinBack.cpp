#include "BSpinBack.h"

BSpinBack::BSpinBack()
{
	Requires(Robot::bouffeurAvant.get());
}

// Called just before this Command runs the first time
void BSpinBack::Initialize()
{
	Robot::bouffeurAvant->SpinInverse();
}

// Called repeatedly when this Command is scheduled to run
void BSpinBack::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool BSpinBack::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void BSpinBack::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BSpinBack::Interrupted()
{

}
