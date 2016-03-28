#include "Camera.h"
#include "../RobotMap.h"
#include "../Commands/AutomaticCapture.h"
#include <cmath>

int Camera::hueMin(31);
int Camera::hueMax(152);
int Camera::satMin(163);
int Camera::satMax(255);
int Camera::valMin(44);
int Camera::valMax(233);
int Camera::aireMin(200);

double Camera::distance(0);
double Camera::ecart(0);
double Camera::CAMERA_OFFSET(0);

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

	analysed = false;

}

void Camera::InitDefaultCommand()
{
	SetDefaultCommand(new AutomaticCapture());
}

void Camera::SendImage() {
	IMAQdxGrab(session, frame, true, NULL);

	CameraServer::GetInstance()->SetImage(frame);
}

void Camera::GetInfo() {

	analysed = false;

	Image* binFrame;

	binFrame = imaqCreateImage(IMAQ_IMAGE_U8, 0);

	Range Hue = {hueMin, hueMax};
	Range Sat = {satMin, satMax};
	Range Val = {valMin, valMax};

	ParticleFilterCriteria2 criteria[1];
	ParticleFilterOptions2 filterOptions = {0, 0, 1, 1};


	criteria[0] = {IMAQ_MT_AREA, 0, aireMin, false, true};

	int nbParticles(0);

	IMAQdxGrab(session, frame, true, NULL);
	imaqScale(frame, frame, 2, 2, ScalingMode::IMAQ_SCALE_SMALLER, IMAQ_NO_RECT);
	imaqColorThreshold(binFrame, frame, 255, IMAQ_HSV, &Hue, &Sat, &Val);
	imaqMorphology(binFrame, binFrame, IMAQ_DILATE, NULL);
	//imaqParticleFilter4(binFrame, binFrame, &criteria[0], 1, &filterOptions, NULL, &nbParticles);

	imaqCountParticles(binFrame, 0, &nbParticles);

	CameraServer::GetInstance()->SetImage(binFrame);

	int indexMax(0);
	double aireMax(0);

	if(nbParticles > 0) {

		for(int particleIndex = 0; particleIndex < nbParticles; particleIndex++){

			double aire (0);
			imaqMeasureParticle(binFrame, particleIndex, 0, IMAQ_MT_AREA, &aire);

			if (aire > aireMax){
				aireMax = aire;
				indexMax = particleIndex;
			}
		}


		double hypothenuse(0);

		int hauteurImage(0);
		int largeurImage(0);

		double centreX(0);
		double centreY(0);
		double angleX(0);
		double angleY(0);
		double offset(0);

		imaqMeasureParticle(binFrame, indexMax, 0, IMAQ_MT_CENTER_OF_MASS_X, &centreX);
		imaqMeasureParticle(binFrame, indexMax, 0, IMAQ_MT_CENTER_OF_MASS_Y, &centreY);

		imaqGetImageSize(binFrame, &largeurImage, &hauteurImage);
		double dHauteurImage(hauteurImage);
		double dLargeurImage(largeurImage);


		//Normalisation
		centreX = ((2 * centreX) / dLargeurImage) - 1;
		centreY = ((-2 * centreY) / dHauteurImage) + 1;


		angleX = atan(centreX * tan(FOV_X * acos(-1) / 180.0));
		angleY = atan(centreY * tan(FOV_Y * acos(-1) / 180.0));

		distance = (TARGET_HEIGHT - CAMERA_HEIGHT) / tan(CAMERA_ANGLE * acos(-1) / 180 + angleY);
		hypothenuse = sqrt(pow(distance, 2) + pow(TARGET_HEIGHT - CAMERA_HEIGHT, 2));

		offset = hypothenuse * tan(angleX);

		ecart = offset - CAMERA_OFFSET;


		SmartDashboard::PutNumber("Distance Cible", distance);
		SmartDashboard::PutNumber("Angle Cible", ecart);
		SmartDashboard::PutNumber("Aire Particule", aireMax);
		SmartDashboard::PutNumber("Nombre Particules", nbParticles);
		SmartDashboard::PutNumber("Hypothenuse", hypothenuse);
		SmartDashboard::PutNumber("Largeur image", largeurImage);
	}

	analysed = true;

}


void Camera::StartAnalyse() {

	analysed = false;

}

bool Camera::HasAnalysed() {

	return analysed;
}
