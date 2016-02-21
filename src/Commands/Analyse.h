#ifndef ANALYSE_H
#define ANALYSE_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class Analyse: public Command
{
public:
	Analyse();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
