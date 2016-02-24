#ifndef CSETSHOOT_H
#define CSETSHOOT_h


#include "Commands/Subsystem.h"
#include "../Robot.h"


class CSetShoot: public Command {
public:

	enum Position {Shoot, Min};

	CSetShoot();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();


};

#endif
