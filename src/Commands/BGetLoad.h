#ifndef BGETLOAD_H
#define BGETLOAD_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class BGetLoad: public Command
{
public:
	BGetLoad();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
