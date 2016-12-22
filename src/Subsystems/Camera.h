#ifndef CAMERA_H
#define CAMERA_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <mutex>
#include <thread>
#include <memory>


//include sur

class Camera: public Subsystem
{
private:
	std::shared_ptr<USBCamera> cam;
	IMAQdxSession session;
	Image* frame;

	double centreX;
	double hauteur;

	mutable std::mutex camMutex;

	std::unique_ptr<std::thread> thread;

	bool m_threadRunning;
	bool m_endThread;

	void InfoRun();


public:

	static int hueMin;
	static int hueMax;
	static int satMin;
	static int satMax;
	static int valMin;
	static int valMax;

	static int aireMin;

	static double CAMERA_OFFSET;

	Camera();
	void InitDefaultCommand();
	void SendImage();
	void GetInfo();
	double GetCentreX() const;
	double GetHauteur() const;
	void StartThread();
	void EndThread();

};



#endif
