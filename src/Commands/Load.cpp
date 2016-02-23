#include "Load.h"
#include "BSetAvant.h"
#include "BWaitLoad.h"
#include "CLoad.h"
#include "BSpinAvant.h"
#include "BStopSpinAvant.h"
#include "CSet.h"


Load::Load()
{
	// Add Commands here:
	// e.g. AddSequential(new Command1());
	//      AddSequential(new Command2());
	// these will run in order.

	// To run multiple commands at the same time,
	// use AddParallel()
	// e.g. AddParallel(new Command1());
	//      AddSequential(new Command2());
	// Command1 and Command2 will run in parallel.

	// A command group will require all of the subsystems that each member
	// would require.
	// e.g. if Command1 requires chassis, and Command2 requires arm,
	// a CommandGroup containing them would require both the chassis and the
	// arm.
	//AddParallel(new CSet(CSet::Position::Min, true)); //catapulte
	//AddSequential(new BSpinAvant()); //bouffeur spin
	//AddSequential(new BSetAvant(BouffeurAvant::Position::Load)); //bouffeur position
	//AddSequential(new BWaitLoad()); //bouffeur
	AddParallel(new BSetAvant(BouffeurAvant::Position::Min)); // bouffeur position
	AddSequential(new CLoad());					//shooter
	//AddSequential(new BStopSpinAvant());		//bouffeur spin

}
