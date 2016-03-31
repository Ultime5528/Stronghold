#include "TakeBoulder.h"

#include "BSpinAvant.h"
#include "BSetBas.h"
#include "BWaitLoad.h"
#include "BGetLoad.h"

TakeBoulder::TakeBoulder()
{
	AddSequential(new BSetBas()); //Descends pendant 1.5s � -0.2
	AddSequential(new BSpinAvant()); //Start spin sans s�curit�
	AddSequential(new BWaitLoad()); //Attends la switch
	AddSequential(new BGetLoad()); //Attends 1s puis arr�te le spin
}
