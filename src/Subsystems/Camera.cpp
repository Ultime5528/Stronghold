#include "Camera.h"
#include "../RobotMap.h"
#include "../Commands/AutomaticCapture.h"

Camera::Camera() :
		Subsystem("Camera")
{
	cam = RobotMap::cameraCam;

	IMAQdxOpenCamera("cam0", IMAQdxCameraControlModeController, &session);
	Wait(0.5);
	IMAQdxConfigureGrab(session);
	Wait(0.5);
	IMAQdxStartAcquisition(session);
	Wait(0.5);
	frame = imaqCreateImage(IMAQ_IMAGE_RGB, 0);

}

void Camera::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultComfrcCreateImage(ImageType::);
	SetDefaultCommand (new AutomaticCapture());
	//CameraServer::GetInstance()->StartAutomaticCapture("cam0");
}

void Camera::SendImage() {
	IMAQdxGrab(session, frame, true, NULL);

	CameraServer::GetInstance()->SetImage(frame);
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
