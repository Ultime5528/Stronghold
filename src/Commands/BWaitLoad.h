#ifndef BWAITLOAD_H
#define BWAITLOAD_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class BWaitLoad: public Command
{
public:

	BWaitLoad();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
