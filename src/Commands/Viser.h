#ifndef VISER_H
#define VISER_H

#include "WPILib.h"

class Viser: public Command
{

public:

	static double distance;
	static double distanceOffset;
	static double offsetX;
	static double rotation;
	static double move;

	Viser(bool shoot = true);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private :
	bool m_shoot;
	bool m_continue = true;
	bool m_rotate = false;
};

#endif
