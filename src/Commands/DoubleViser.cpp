#include "DoubleViser.h"

DoubleViser::DoubleViser()
{

	AddSequential(new Viser(false));
	AddSequential(new WaitCommand(0.7));
	AddSequential(new Viser(true));
	AddSequential(new CSetBas);

}
