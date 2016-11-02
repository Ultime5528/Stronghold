#include "CSetShoot.h"
#include "CMaintien.h"
#include "CSpin.h"
#include "../Subsystems/BouffeurAvant.h"
#include "PMonte.h"

CSetShoot::CSetShoot(bool piston, bool maintien) : Command("CSetShoot")
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::catapulte.get());
	m_piston = piston;
	m_maintien = maintien;
}

// Called just before this Command runs the first time
void CSetShoot::Initialize()
{
	//Robot::catapulte->SetAtShoot();
	if(m_piston)
	Scheduler::GetInstance()->AddCommand(new PMonte());


}

// Called repeatedly when this Command is scheduled to run
void CSetShoot::Execute()
{
	//Robot::catapulte->Reach();
	Robot::catapulte->Up();
}

// Make this return true when this Command no longer needs to run execute()
bool CSetShoot::IsFinished()
{
	//return Robot::catapulte->HasReached();
	return Robot::catapulte->GetPot() <= Catapulte::potShoot;
}

// Called once after isFinished returns true
void CSetShoot::End()
{

	if(m_maintien)
		Scheduler::GetInstance()->AddCommand(new CMaintien());

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CSetShoot::Interrupted()
{
	Robot::catapulte->StopMonte();
}
