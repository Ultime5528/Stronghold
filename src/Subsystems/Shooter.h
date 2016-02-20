#ifndef Shooter_H
#define Shooter_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Shooter: public Subsystem
{
private:

	std::shared_ptr<SpeedController> spin;
	std::shared_ptr<SpeedController> conv;
	std::shared_ptr<DigitalInput> limit;

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Shooter();
	void InitDefaultCommand();
	void StopConv();
	void StopSpin();
	void ConvToBack();
	void ConvThrow();
	void SpinToBack();
	void Spin();
	bool IsLoaded();
};

#endif
