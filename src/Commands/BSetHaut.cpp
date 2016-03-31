#include "BSetHaut.h"

BSetHaut::BSetHaut(bool spin)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::bouffeurAvant.get());
	m_spin = spin;
}

// Called just before this Command runs the first time
void BSetHaut::Initialize()
{
	SetTimeout(3.5);

	if(m_spin)
		Robot::bouffeurAvant->SpinLent();
	else
		Robot::bouffeurAvant->StopSpin();
}

// Called repeatedly when this Command is scheduled to run
void BSetHaut::Execute()
{
	Robot::bouffeurAvant->Up();
}

// Make this return true when this Command no longer needs to run execute()
bool BSetHaut::IsFinished()
{
	return IsTimedOut();
}

// Called once after isFinished returns true
void BSetHaut::End()
{
	Robot::bouffeurAvant->Stop();
	Robot::bouffeurAvant->StopSpin();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BSetHaut::Interrupted()
{
	End();
}
