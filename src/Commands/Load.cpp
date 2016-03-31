#include "Load.h"
#include "CLoad.h"
#include "BSetHaut.h"
#include "CSetBas.h"
#include "BSetBas.h"
#include "CKeep.h"
#include "CSetLoad.h"


Load::Load()
{

	AddSequential(new CSetLoad()); // Monte de peu le shooter
	AddParallel(new CKeep()); //Le maintien toujours

	AddParallel(new BSetHaut(true)); // monte avec TRUE pour spin lent
	AddSequential(new CLoad());		//Attends que la switch soit vraie
	AddParallel(new BSetBas());		//Redescends, stop spin
	AddSequential(new CSetBas());	// Redescends le shooter

}
