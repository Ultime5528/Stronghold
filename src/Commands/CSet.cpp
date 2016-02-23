#include "CSet.h"
#include "CMaintien.h"
#include "CSpin.h"
#include "BSetAvant.h"
#include "../Subsystems/BouffeurAvant.h"

CSet::CSet(Position setpoint, bool another) : Command("CSet")
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::catapulte.get());

	m_setpoint = setpoint;
	m_another = another;
}

// Called just before this Command runs the first time
void CSet::Initialize()
{
	  DriverStation::ReportError("DÉbut de CSet");
	if(m_setpoint == Shoot)
		Robot::catapulte->SetAtShoot();
	else if (m_setpoint == Min)
		Robot::catapulte->SetAtMin();
}

// Called repeatedly when this Command is scheduled to run
void CSet::Execute()
{
	Robot::catapulte->Reach();
}

// Make this return true when this Command no longer needs to run execute()
bool CSet::IsFinished()
{
	return Robot::catapulte->HasReached();
}

// Called once after isFinished returns true
void CSet::End()
{
	  DriverStation::ReportError("Fin Cset");
	if(m_setpoint == Shoot) {
		Scheduler::GetInstance()->AddCommand(new CMaintien());
		Scheduler::GetInstance()->AddCommand(new CSpin());
	}


	if(m_another) {
		Scheduler::GetInstance()->AddCommand(new BSetAvant(BouffeurAvant::Position::Load));
	}

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CSet::Interrupted()
{
	Robot::catapulte->StopMonte();
}
