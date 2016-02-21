#include "CMaintien.h"

CMaintien::CMaintien()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::catapulte.get());
}

// Called just before this Command runs the first time
void CMaintien::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CMaintien::Execute()
{
	Robot::catapulte->Reach();
}

// Make this return true when this Command no longer needs to run execute()
bool CMaintien::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void CMaintien::End()
{
	Robot::catapulte->StopMonte();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CMaintien::Interrupted()
{
	End();
}
