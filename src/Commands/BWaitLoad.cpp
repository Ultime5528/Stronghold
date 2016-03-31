#include "BWaitLoad.h"
#include "../Subsystems/BouffeurAvant.h"
#include "Load.h"
#include "BGetLoad.h"

BWaitLoad::BWaitLoad() : Command("BWaitLoad")
{
	Requires(Robot::bouffeurAvant.get());
}



void BWaitLoad::Initialize()
{

}


void BWaitLoad::Execute()
{


}


bool BWaitLoad::IsFinished()
{
	return Robot::bouffeurAvant->IsPressed();
}


void BWaitLoad::End()
{

	//Scheduler::GetInstance()->AddCommand(new BGetLoad());

}


void BWaitLoad::Interrupted()
{
  End();
}
