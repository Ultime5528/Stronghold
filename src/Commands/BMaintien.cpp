#include "BMaintien.h"

BMaintien::BMaintien()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::bouffeurAvant.get());
}

// Called just before this Command runs the first time
void BMaintien::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void BMaintien::Execute()
{
	Robot::bouffeurAvant->Reach();
}

// Make this return true when this Command no longer needs to run execute()
bool BMaintien::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void BMaintien::End()
{
	Robot::bouffeurAvant->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BMaintien::Interrupted()
{
}
