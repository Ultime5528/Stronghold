#include "BWaitLoad.h"
#include "BSetAvant.h"
#include "../Subsystems/BouffeurAvant.h"
#include "Load.h"

BWaitLoad::BWaitLoad() : Command("BWaitLoad")
{
	Requires(Robot::bouffeurAvant.get());
		Robot::bouffeurAvant->SetSetpoint(BouffeurAvant::Position::Load);
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time

	void BWaitLoad::Initialize()
{
		DriverStation::ReportError("Entree BWaitLoad");
}

// Called repeatedly when this Command is scheduled to run
void BWaitLoad::Execute()
{
	Robot::bouffeurAvant->Reach();

}

// Make this return true when this Command no longer needs to run execute()
bool BWaitLoad::IsFinished()
{

	return Robot::bouffeurAvant->IsPressed();
}

// Called once after isFinished returns true
void BWaitLoad::End()
{
	DriverStation::ReportError("Fin BWaitLoad");                                         //"Antoine becomes captain" - 2/22/2016 5:35
	Scheduler::GetInstance()->AddCommand(new Load());

	//Scheduler::GetInstance()->AddCommand(new BSetAvant(BouffeurAvant::Position::Min));
  //Robot::bouffeurAvant->Stop();

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BWaitLoad::Interrupted()
{
  End();
}
