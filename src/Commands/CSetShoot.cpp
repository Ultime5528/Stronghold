#include "CSetShoot.h"
#include "CMaintien.h"
#include "CSpin.h"
#include "Analyse.h"
#include "../Subsystems/BouffeurAvant.h"

CSetShoot::CSetShoot() : Command("CSetShoot")
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::catapulte.get());

}

// Called just before this Command runs the first time
void CSetShoot::Initialize()
{
	Robot::catapulte->SetAtShoot();
}

// Called repeatedly when this Command is scheduled to run
void CSetShoot::Execute()
{
	Robot::catapulte->Reach();
}

// Make this return true when this Command no longer needs to run execute()
bool CSetShoot::IsFinished()
{
	return Robot::catapulte->HasReached();
}

// Called once after isFinished returns true
void CSetShoot::End()
{

	Scheduler::GetInstance()->AddCommand(new CMaintien());
	Scheduler::GetInstance()->AddCommand(new Analyse());

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CSetShoot::Interrupted()
{
	Robot::catapulte->StopMonte();
}
