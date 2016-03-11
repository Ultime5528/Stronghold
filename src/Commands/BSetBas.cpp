#include "BSetBas.h"

BSetBas::BSetBas()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::bouffeurAvant.get());
}

// Called just before this Command runs the first time
void BSetBas::Initialize()
{
	SetTimeout(1.5);
}

// Called repeatedly when this Command is scheduled to run
void BSetBas::Execute()
{
	Robot::bouffeurAvant->Down();
}

// Make this return true when this Command no longer needs to run execute()
bool BSetBas::IsFinished()
{
	return IsTimedOut();
}

// Called once after isFinished returns true
void BSetBas::End()
{
	Robot::bouffeurAvant->Stop();
	Robot::bouffeurAvant->StopSpin();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BSetBas::Interrupted()
{
	End();
}
