#ifndef CMAINTIEN_H
#define CMAINTIEN_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class CMaintien: public Command {

public:
	CMaintien();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
