#ifndef VISER_H
#define VISER_H

#include "WPILib.h"
#include "memory"
#include <mutex>
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
	void SetParameters(double hauteur, double centreX);

private :

	std::unique_ptr<frc::PIDCalculator> forwardPID;
	std::unique_ptr<frc::PIDCalculator> rotatePID;

	bool m_isFinished;
	double m_hauteur;
	double m_centreX;

	std::mutex m_mutex;

	//Timer timer;

};

#endif
