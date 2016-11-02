#include "CSetBas.h"
#include "../Subsystems/Catapulte.h"
#include "PRetract.h"

CSetBas::CSetBas(bool piston) : Command("CSetBas")
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::catapulte.get());
	m_piston = piston;
}

// Called just before this Command runs the first time
void CSetBas::Initialize()
{
	//Robot::catapulte->SetAtMin();
	if(m_piston)
	Scheduler::GetInstance()->AddCommand(new PRetract());

}

// Called repeatedly when this Command is scheduled to run
void CSetBas::Execute()
{
	Robot::catapulte->Down();
}

// Make this return true when this Command no longer needs to run execute()
bool CSetBas::IsFinished()
{
	//return Robot::catapulte->HasReached();
	return Robot::catapulte->GetPot() >= Catapulte::potMax;
}

// Called once after isFinished returns true
void CSetBas::End()
{
	return Robot::catapulte->StopMonte();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CSetBas::Interrupted()
{
	End();
}
