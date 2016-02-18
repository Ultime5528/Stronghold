#ifndef BStopSpinAvant_H
#define BStopSpinAvant_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

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
