#ifndef BSETHAUT_H
#define BSETHAUT_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

class BSetHaut: public Command
{
private:
	bool m_spin;

public:
	BSetHaut(bool spin = false);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif
