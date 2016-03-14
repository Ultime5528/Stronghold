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
	//cam = RobotMap::cameraCam;

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
<<<<<<< HEAD
	// Set the default command for a subsystem here.
	//SetDefaultComfrcCreateImage(ImageType::);
	SetDefaultCommand (new AutomaticCapture());
	//CameraServer::GetInstance()->StartAutomaticCapture("cam0");
=======
	SetDefaultCommand(new AutomaticCapture());
>>>>>>> origin/fin-base-pilotable
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
	//Range HueDeux = { 19,65 };
	//Range ValDeux = { 87,177};
	//Range SatDeux = {48,77 };

	ParticleFilterCriteria2 criteria[3];
	//ParticleFilterOptions2 filterOptions = {0, 0, 1, 1};


	criteria[0] = {IMAQ_MT_AREA, 0, 200, false, true};
	criteria[1] = {IMAQ_MT_BOUNDING_RECT_HEIGHT, 0, 1000, false, false};
	criteria[2] = {IMAQ_MT_BOUNDING_RECT_WIDTH,0 ,1000, false, false};

	//int nbParticles(0);

	IMAQdxGrab(session, frame, true, NULL);
<<<<<<< HEAD
	//imaqScale(frame, frame, 2, 2, ScalingMode::IMAQ_SCALE_SMALLER, IMAQ_NO_RECT);
	imaqColorThreshold(binFrame, frame, 255, IMAQ_HSV, &Hue, &Sat, &Val);
	//imaqColorThreshold(binFrame, frame, 1, IMAQ_HSV, &HueDeux, &SatDeux, &ValDeux);
	//imaqMorphology(binFrame, binFrame, IMAQ_DILATE, NULL);
	//imaqParticleFilter4(binFrame, binFrame, &criteria[0], 3, &filterOptions, NULL, &nbParticles);
=======
	imaqScale(frame, frame, 2, 2, ScalingMode::IMAQ_SCALE_SMALLER, IMAQ_NO_RECT);
	imaqColorThreshold(binFrame, frame, 1, IMAQ_HSV, &Hue, &Sat, &Val);
	imaqColorThreshold(binFrame, frame, 1, IMAQ_HSV, &HueDeux, &SatDeux, &ValDeux);
	imaqMorphology(binFrame, binFrame, IMAQ_DILATE, NULL);
	imaqParticleFilter4(binFrame, binFrame, &criteria[0], 3, &filterOptions, NULL, &nbParticles);
>>>>>>> origin/fin-base-pilotable

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
		double hypotenuse(0);
		int hauteurImage(0);
		int largeurImage(0);

		double centre(0);

		imaqMeasureParticle(binFrame, indexMax, 0, IMAQ_MT_BOUNDING_RECT_WIDTH, &largeurParticule);
		imaqMeasureParticle(binFrame, indexMax, 0, IMAQ_MT_CENTER_OF_MASS_X, &centre);

		imaqGetImageSize(binFrame, &largeurImage, &hauteurImage);

		double dHauteurImage(hauteurImage);
		double dLargeurImage(largeurImage);

		hypotenuse = ((1*dLargeurImage) / (2*largeurParticule*0.5914));
		distance = sqrt(pow(hypotenuse, 2) - 50.17361106388889);


<<<<<<< HEAD
=======
		centre = 2 * centre / dLargeurImage - 1;

		angle = atan(centre * 0.5914) + 4;

		SmartDashboard::PutNumber("Angle", angle);
		SmartDashboard::PutNumber("Distance", distance);
		SmartDashboard::PutNumber("Largeur particule", dLargeurImage);


	}

	analysed = true;
>>>>>>> origin/fin-base-pilotable

}


void Camera::StartAnalyse() {

	analysed = false;

}

bool Camera::HasAnalysed() {

	return analysed;
}
