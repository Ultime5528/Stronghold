#ifndef CSETBAS_H
#define CSETBAS_H

#include "Commands/Subsystem.h"
#include "../Robot.h"

class CSetBas: public Command
{
private:
	bool m_piston;
public:
	CSetBas(bool piston = false);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
