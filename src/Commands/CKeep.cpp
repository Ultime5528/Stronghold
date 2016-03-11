#include "CKeep.h"

CKeep::CKeep()
{
	Requires(Robot::catapulte.get());
}

// Called just before this Command runs the first time
void CKeep::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CKeep::Execute()
{
	Robot::catapulte->MaintienLoad();
}

// Make this return true when this Command no longer needs to run execute()
bool CKeep::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void CKeep::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CKeep::Interrupted()
{

}
