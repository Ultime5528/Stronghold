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


	double FOV_X = 23.99;
	double FOV_Y = 18.46;
	double CAMERA_ANGLE = 30.0;
	double CAMERA_HEIGHT = 0.75;

	double TARGET_HEIGHT = 2.286;

public:

	static int hueMin;
	static int hueMax;
	static int satMin;
	static int satMax;
	static int valMin;
	static int valMax;

	static int aireMin;

	static double distance;

	static double ecart;

	static double CAMERA_OFFSET;


	Camera();
	void InitDefaultCommand();
	void SendImage();
	void GetInfo();

};



#endif
