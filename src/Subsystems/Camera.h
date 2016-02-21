#ifndef CAMERA_H
#define CAMERA_H

#include "Commands/Subsystem.h"
#include "WPILib.h"


//include sur

class Camera: public Subsystem
{
private:
	std::shared_ptr<USBCamera> cam;
	IMAQdxSession session;
	Image* frame;

	bool analysed;

public:

	static int hueMin;
	static int hueMax;
	static int satMin;
	static int satMax;
	static int valMin;
	static int valMax;

	static double distance;
	static double angle;

	Camera();
	void InitDefaultCommand();
	void SendImage();
	void GetInfo();
	void StartAnalyse();
	bool HasAnalysed();
};



#endif
