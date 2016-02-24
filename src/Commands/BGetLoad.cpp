#include "BGetLoad.h"

BGetLoad::BGetLoad()
{
	Requires(Robot::bouffeurAvant.get());
}

// Called just before this Command runs the first time
void BGetLoad::Initialize()
{
	SetTimeout(1);
}

// Called repeatedly when this Command is scheduled to run
void BGetLoad::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool BGetLoad::IsFinished()
{
	return IsTimedOut();
}

// Called once after isFinished returns true
void BGetLoad::End()
{
	Robot::bouffeurAvant->StopSpin();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BGetLoad::Interrupted()
{

}
