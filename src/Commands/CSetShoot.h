#ifndef CSETSHOOT_H
#define CSETSHOOT_h


#include "Commands/Subsystem.h"
#include "../Robot.h"


class CSetShoot: public Command {
private:
	bool m_piston;
	bool m_maintien;

public:

	enum Position {Shoot, Min};

	CSetShoot(bool piston = false, bool m_piston = true);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();


};

#endif
