#include "Reset.h"

Reset::Reset()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void Reset::Initialize()
{
	Scheduler::GetInstance()->RemoveAll();
}

// Called repeatedly when this Command is scheduled to run
void Reset::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool Reset::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void Reset::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Reset::Interrupted()
{

}
