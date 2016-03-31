#include "CSetLoad.h"
#include "Load.h"
#include "CKeep.h"

CSetLoad::CSetLoad()
{
	Requires(Robot::catapulte.get());
	m_init = 0.43;
}

// Called just before this Command runs the first time
void CSetLoad::Initialize()
{
	m_init = Robot::catapulte->GetPot();
}

// Called repeatedly when this Command is scheduled to run
void CSetLoad::Execute()
{
	Robot::catapulte->Up();
}

// Make this return true when this Command no longer needs to run execute()
bool CSetLoad::IsFinished()
{
	return (Robot::catapulte->GetPot() < (m_init - 0.025) );
}

// Called once after isFinished returns true
void CSetLoad::End()
{
	Robot::catapulte->StopMonte();
	//Scheduler::GetInstance()->AddCommand(new CKeep());
	//Scheduler::GetInstance()->AddCommand(new Load());
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CSetLoad::Interrupted()
{

}
