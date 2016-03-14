#include "Load.h"
#include "BWaitLoad.h"
#include "CLoad.h"
#include "BSpinAvant.h"
#include "BStopSpinAvant.h"
#include "BSetHaut.h"
#include "CSetBas.h"


Load::Load()
{

	//AddParallel(new CSet(CSet::Position::Min, true)); //catapulte
	//AddSequential(new BSpinAvant()); //bouffeur spin
	//AddSequential(new BSetAvant(BouffeurAvant::Position::Load)); //bouffeur position
	//AddSequential(new BWaitLoad()); //bouffeur
	AddParallel(new BSetHaut(true)); // bouffeur position
	AddSequential(new CLoad());					//shooter
	AddSequential(new CSetBas());
	//AddSequential(new BStopSpinAvant());		//bouffeur spin

}
