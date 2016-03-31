#include "BStopSpinAvant.h"

BStopSpinAvant::BStopSpinAvant() : Command("BStopSpinAvant")
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::bouffeurAvant.get());
}


// Called just before this Command runs the first time
void BStopSpinAvant::Initialize()
{
	Robot::bouffeurAvant->StopSpin();
}

// Called repeatedly when this Command is scheduled to run
void BStopSpinAvant::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool BStopSpinAvant::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void BStopSpinAvant::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BStopSpinAvant::Interrupted()
{

}
