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
	static double angleX;
	static double angleY;

	int FOV_X=23.99;
	int FOV_Y=18.46;
	int CAMERA_ANGLE=30;
	int CAMERA_HEIGHT=.75;
	int CAMERA_OFFSET=.18;//Simon est cho aussi
	int TARGET_HEIGHT=2.286;		//Émile est chaud au boute -Younes 2k16


	Camera();
	void InitDefaultCommand();
	void SendImage();
	void GetInfo();
	void StartAnalyse();
	bool HasAnalysed();
};



#endif
