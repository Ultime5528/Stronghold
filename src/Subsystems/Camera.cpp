#include "Camera.h"
#include "../RobotMap.h"
#include "../Commands/AutomaticCapture.h"
#include <cmath>

int Camera::hueMin(31);
int Camera::hueMax(152);
int Camera::satMin(99);
int Camera::satMax(255);
int Camera::valMin(44);
int Camera::valMax(233);

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


	criteria[0] = {IMAQ_MT_AREA, 0, 200, false, true};

	int nbParticles(0);

	IMAQdxGrab(session, frame, true, NULL);
	imaqScale(frame, frame, 2, 2, ScalingMode::IMAQ_SCALE_SMALLER, IMAQ_NO_RECT);
	imaqColorThreshold(binFrame, frame, 1, IMAQ_HSV, &Hue, &Sat, &Val);

	imaqMorphology(binFrame, binFrame, IMAQ_DILATE, NULL);
	imaqParticleFilter4(binFrame, binFrame, &criteria[0], 1, &filterOptions, NULL, NULL);
	imaqCountParticles(binFrame, 1, &nbParticles);
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

		double largeurParticule(0);
		double hauteurParticule(0);
		double hypotenuse(0);
		double posXParticule(0);
		int hauteurImage(0);
		int largeurImage(0);

		double centre(0);

		imaqMeasureParticle(binFrame, indexMax, 0, IMAQ_MT_BOUNDING_RECT_HEIGHT, &hauteurParticule);
		imaqMeasureParticle(binFrame, indexMax, 0, IMAQ_MT_BOUNDING_RECT_WIDTH, &largeurParticule);
		imaqMeasureParticle(binFrame, indexMax, 0, IMAQ_MT_CENTER_OF_MASS_X, &centre);
		imaqGetImageSize(binFrame, &largeurImage, &hauteurImage);

		double dHauteurParticule(hauteurParticule);
		double dLargeurParticule(largeurParticule);
		double dHauteurImage(hauteurImage);
		double dLargeurImage(largeurImage);

		hypotenuse = ((1*dLargeurImage) / (2*largeurParticule*0.5914));
		distance = sqrt(pow(hypotenuse, 2.0) - 50.17361106388889);

		centre = 2 * centre / dLargeurImage - 1;

		angle = atan(centre * 0.449417)* 180 / acos(-1);


		SmartDashboard::PutNumber("Distance Cible", distance);
		SmartDashboard::PutNumber("Angle Cible", angle);
		SmartDashboard::PutNumber("Aire Particule", aireMax);
		SmartDashboard::PutNumber("Nombre Particules", nbParticles);
		SmartDashboard::PutNumber("Hypothenuse", hypotenuse);
		SmartDashboard::PutNumber("Largeur particule", largeurParticule);
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
