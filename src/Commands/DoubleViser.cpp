#include "DoubleViser.h"
#include "Viser.h"
#include "CSetBas.h"

DoubleViser::DoubleViser()
{

	AddSequential(new Viser());
	AddSequential(new WaitCommand(0.7));
	AddSequential(new Viser());

}
