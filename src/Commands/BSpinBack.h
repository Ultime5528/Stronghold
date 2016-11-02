#ifndef BSPINBACK_H
#define BSPINBACK_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class BSpinBack: public Command
{
public:
	BSpinBack();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
