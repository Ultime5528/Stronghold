#include "BSetLoad.h"
#include "BWaitLoad.h"

BSetLoad::BSetLoad()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::bouffeurAvant.get());
}

// Called just before this Command runs the first time
void BSetLoad::Initialize()
{
	SetTimeout(1.5);
	Robot::bouffeurAvant->Spin();
}

// Called repeatedly when this Command is scheduled to run
void BSetLoad::Execute()
{
	Robot::bouffeurAvant->Down();

}

// Make this return true when this Command no longer needs to run execute()
bool BSetLoad::IsFinished()
{
	return IsTimedOut();
}

// Called once after isFinished returns true
void BSetLoad::End()
{
	Scheduler::GetInstance()->AddCommand(new BWaitLoad());
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BSetLoad::Interrupted()
{

}
