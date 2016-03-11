#ifndef CSETLOAD_H
#define CSETLOAD_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class CSetLoad: public Command
{
private:

	double m_init;

public:
	CSetLoad();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
