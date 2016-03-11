#include "BWaitLoad.h"
#include "../Subsystems/BouffeurAvant.h"
#include "Load.h"
#include "BGetLoad.h"

BWaitLoad::BWaitLoad() : Command("BWaitLoad")
{
	Requires(Robot::bouffeurAvant.get());
}

// Called just before this Command runs the first time

void BWaitLoad::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void BWaitLoad::Execute()
{


}

// Make this return true when this Command no longer needs to run execute()
bool BWaitLoad::IsFinished()
{
	return Robot::bouffeurAvant->IsPressed();
}

// Called once after isFinished returns true
void BWaitLoad::End()
{
	                                         //"Antoine becomes captain" - 2/22/2016 5:35
	Scheduler::GetInstance()->AddCommand(new BGetLoad());

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void BWaitLoad::Interrupted()
{
  End();
}
