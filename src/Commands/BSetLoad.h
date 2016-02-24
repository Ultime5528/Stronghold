#ifndef BSETLOAD_H
#define BSETLOAD_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class BSetLoad: public Command
{
public:
	BSetLoad();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
