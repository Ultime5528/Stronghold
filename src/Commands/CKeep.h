#ifndef CKEEP_H
#define CKEEP_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class CKeep: public Command
{
public:
	CKeep();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
