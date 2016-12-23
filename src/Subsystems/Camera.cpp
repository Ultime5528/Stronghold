#include "Camera.h"
#include "../RobotMap.h"
#include "../Commands/AutomaticCapture.h"
#include <cmath>
#include <functional>
#include <utility>


int Camera::hueMin(44);
int Camera::hueMax(137);
int Camera::satMin(156);
int Camera::satMax(255);
int Camera::valMin(140);
int Camera::valMax(231);
int Camera::aireMin(200);

double Camera::CAMERA_OFFSET(0.15);


Camera::Camera() :
		Subsystem("Camera"),
		thread(nullptr),
		m_threadRunning(false),
		m_endThread(false)
{
	//cam = RobotMap::cameraCam;

	IMAQdxOpenCamera("cam0", IMAQdxCameraControlModeController, &session);
	//Wait(0.5);
	IMAQdxConfigureGrab(session);
	//Wait(0.5);
	IMAQdxStartAcquisition(session);
	//Wait(0.5);
	frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);
	centreX = 0;
	hauteur = 0;

}

void Camera::InitDefaultCommand()
{
	//SetDefaultCommand(new AutomaticCapture());
}

void Camera::SendImage() {
	IMAQdxGrab(session, frame, true, NULL);

	CameraServer::GetInstance()->SetImage(frame);
}

void Camera::GetInfo(SetParamHandler func) {

	Image* binFrame = imaqCreateImage(IMAQ_IMAGE_U8, 0);

	Range Hue = {hueMin, hueMax};
	Range Sat = {satMin, satMax};
	Range Val = {valMin, valMax};

	int nbParticles(0);
	int indexMax(0);
	int imgHauteur(0), imgLargeur(0);
	double aireMax(0);
	double aire(0);

	IMAQdxGrab(session, frame, true, NULL);
	imaqScale(frame, frame, 2, 2, ScalingMode::IMAQ_SCALE_SMALLER, IMAQ_NO_RECT);
	imaqColorThreshold(binFrame, frame, 255, IMAQ_HSV, &Hue, &Sat, &Val);
	imaqMorphology(binFrame, binFrame, IMAQ_DILATE, NULL);

	imaqGetImageSize(binFrame, &imgLargeur, &imgHauteur);

	imaqCountParticles(binFrame, 0, &nbParticles);


	CameraServer::GetInstance()->SetImage(binFrame);

	if(nbParticles > 0) {

		for(int particleIndex = 0; particleIndex < nbParticles; particleIndex++){

			imaqMeasureParticle(binFrame, particleIndex, 0, IMAQ_MT_AREA, &aire);

			if (aire > aireMax){
				aireMax = aire;
				indexMax = particleIndex;
			}
		}


		SmartDashboard::PutNumber("Aire Particule", aireMax);
		SmartDashboard::PutNumber("Nombre Particules", nbParticles);


		//Lock sur les deux infos accessibles
		{
			std::lock_guard<std::mutex> lock(camMutex);

			imaqMeasureParticle(binFrame, indexMax, 0, IMAQ_MT_CENTER_OF_MASS_X, &centreX);
			imaqMeasureParticle(binFrame, indexMax, 0, IMAQ_MT_BOUNDING_RECT_HEIGHT, &hauteur);

			SmartDashboard::PutNumber("Centre X", centreX);
			SmartDashboard::PutNumber("Hauteur particule", hauteur);
			SmartDashboard::PutNumber("Hauteur image", imgHauteur);

			//Normalisation

			centreX = 2 * centreX / (double) imgLargeur - 1;
			hauteur /= (double) imgHauteur;

			SmartDashboard::PutNumber("Centre X Norm", centreX);
			SmartDashboard::PutNumber("Hauteur particule Norm", hauteur);

			if(func)
				func(hauteur, centreX);

		}

	}

}

double Camera::GetCentreX() const {
	std::lock_guard<std::mutex> lock(camMutex);
	return centreX;
}

double Camera::GetHauteur() const {
	std::lock_guard<std::mutex> lock(camMutex);
	return hauteur;
}


void Camera::EndThread() {
	m_endThread = true;
}

void Camera::InfoRun(SetParamHandler func) {

	DriverStation::ReportError("Début thread");

	do {
		GetInfo(func);
		Wait(0.10);

	} while(!m_endThread);

	DriverStation::ReportError("Fin thread");

	m_threadRunning = false;

}


