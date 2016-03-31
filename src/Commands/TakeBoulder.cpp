#include "TakeBoulder.h"

#include "BSpinAvant.h"
#include "BSetBas.h"
#include "BWaitLoad.h"
#include "BGetLoad.h"

TakeBoulder::TakeBoulder()
{
	AddSequential(new BSetBas()); //Descends pendant 1.5s à -0.2
	AddSequential(new BSpinAvant()); //Start spin sans sécurité
	AddSequential(new BWaitLoad()); //Attends la switch
	AddSequential(new BGetLoad()); //Attends 1s puis arrête le spin
}
