#ifndef BSETAVANT_H
#define BSETAVANT_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class CSet: public Command {
public:

	enum Position {Max, Min};

	CSet(Position setpoint);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	Position m_setpoint;

};

#endif
