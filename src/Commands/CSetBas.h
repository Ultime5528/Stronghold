#ifndef CSETBAS_H
#define CSETBAS_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class CSetBas: public Command
{
public:
	CSetBas();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
