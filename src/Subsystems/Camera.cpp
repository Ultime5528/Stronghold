#include "Camera.h"
#include "../RobotMap.h"
#include "../Commands/AutomaticCapture.h"
#include <cmath>

int Camera::hueMin(0);
int Camera::hueMax(255);
int Camera::satMin(0);
int Camera::satMax(255);
int Camera::valMin(0);
int Camera::valMax(255);

double Camera::distance(0);
double Camera::angle(0);

Camera::Camera() :
		Subsystem("Camera")
{
	cam = RobotMap::cameraCam;

	IMAQdxOpenCamera("cam0", IMAQdxCameraControlModeController, &session);
	//Wait(0.5);
	IMAQdxConfigureGrab(session);
	//Wait(0.5);
	IMAQdxStartAcquisition(session);
	//Wait(0.5);
	frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);

}

void Camera::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultComfrcCreateImage(ImageType::);
	//SetDefaultCommand (new AutomaticCapture());
	//CameraServer::GetInstance()->StartAutomaticCapture("cam0");
}

void Camera::SendImage() {
	IMAQdxGrab(session, frame, true, NULL);

	CameraServer::GetInstance()->SetImage(frame);
}
void Camera::GetInfo() {
	Image* binFrame;

	binFrame = imaqCreateImage(IMAQ_IMAGE_U8, 0);

	Range Hue = {hueMin, hueMax};
	Range Sat = {satMin, satMax};
	Range Val = {valMin, valMax};
	Range HueDeux = { 19,65 };
	Range ValDeux = { 87,177};
	Range SatDeux = {48,77 };

	ParticleFilterCriteria2 criteria[3];
	ParticleFilterOptions2 filterOptions = {0, 0, 1, 1};


	criteria[0] = {IMAQ_MT_AREA, 0, 200, false, true};
	criteria[1] = {IMAQ_MT_BOUNDING_RECT_HEIGHT, 0, 1000, false, false};
	criteria[2] = {IMAQ_MT_BOUNDING_RECT_WIDTH,0 ,1000, false, false};

	int nbParticles(0);

	IMAQdxGrab(session, frame, true, NULL);
	//imaqScale(frame, frame, 2, 2, ScalingMode::IMAQ_SCALE_SMALLER, IMAQ_NO_RECT);
	imaqColorThreshold(binFrame, frame, 1, IMAQ_HSV, &Hue, &Sat, &Val);
	//imaqColorThreshold(binFrame, frame, 1, IMAQ_HSV, &HueDeux, &SatDeux, &ValDeux);
	imaqMorphology(binFrame, binFrame, IMAQ_DILATE, NULL);
	//imaqParticleFilter4(binFrame, binFrame, &criteria[0], 3, &filterOptions, NULL, &nbParticles);

	CameraServer::GetInstance()->SetImage(binFrame);



}


// Put methods for controlling this subsystem
// here. Call these from Commands.
