#ifndef Camera_H
#define Camera_H

#include "Commands/Subsystem.h"
#include "WPILib.h"


//include sur

class Camera: public Subsystem
{
private:
	std::shared_ptr<USBCamera> cam;
	IMAQdxSession session;
	Image* frame;
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	static double distance;
	static double angle;
	Camera();
	void InitDefaultCommand();
	void SendImage();
	void GetInfo();
};



#endif
