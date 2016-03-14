#ifndef BSTOPSPINAVANT_H
#define BSTOPSPINAVANT_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../Robot.h"

class BStopSpinAvant: public Command
{
public:
	BStopSpinAvant();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
