#ifndef BSETBAS_H
#define BSETBAS_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class BSetBas: public Command
{
public:
	BSetBas();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
