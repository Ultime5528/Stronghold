#ifndef VISER_H
#define VISER_H

#include "WPILib.h"
#include "../Others/PIDCalculator.h"

class Viser: public Command
{

public:

	static double TARGET_H;
	static double TARGET_H_OFFSET;
	static double TARGET_X;
	static double TARGET_X_OFFSET;

	static double FORWARD_P;
	static double FORWARD_I;
	static double FORWARD_D;

	static double ROTATE_P;
	static double ROTATE_I;
	static double ROTATE_D;

	Viser(bool shoot = true);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

private :

	frc::PIDCalculator* forwardPID;
	frc::PIDCalculator* rotatePID;

	bool m_finished;


	//Timer timer;

};

#endif
