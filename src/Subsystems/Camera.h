#ifndef CAMERA_H
#define CAMERA_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <mutex>
#include <thread>
#include <memory>


typedef std::function<void(double,double)> SetParamHandler;

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

	void InfoRun(SetParamHandler func = SetParamHandler());


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
	void GetInfo(SetParamHandler func = SetParamHandler());
	double GetCentreX() const;
	double GetHauteur() const;

	void EndThread();

	template <typename Callable, typename Arg>
	void StartThread(Callable&& f, Arg&& arg) {

		using namespace std::placeholders;

		SetParamHandler func =
				std::bind(std::forward<Callable>(f), std::forward<Arg>(arg), _1, _2);

		if(!m_threadRunning) {
			m_threadRunning = true;
			m_endThread = false;

			if(thread) {
				thread->join();
				thread.reset();
			}


			DriverStation::ReportError("Start new thread in StartThread()");

			thread.reset( new std::thread([=] { InfoRun(func); }) );
		}
		else {
			DriverStation::ReportError("Can't start new Cam Thread. Already running.");
		}

	}

};



#endif
