#ifndef RESET_H
#define RESET_H

#include "WPILib.h"

class Reset: public Command
{
public:
	Reset();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
