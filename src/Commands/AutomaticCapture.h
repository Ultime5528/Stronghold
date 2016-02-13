#ifndef AutomaticCapture_H
#define AutomaticCapture_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class AutomaticCapture: public Command
{
public:
	AutomaticCapture();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
