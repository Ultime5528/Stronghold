#include "Viser.h"
#include "Shoot.h"
#include "../Subsystems/Camera.h"
#include "../Robot.h"
#include <cmath>

double Viser::distance(1.5);
double Viser::distanceOffset(0.1);
double Viser::offsetX(0.1);
double Viser::rotation(0.4);
double Viser::move(0.5);


Viser::Viser(bool shoot) : Command("Viser")
{
	Requires(Robot::basePilotable.get());
	Requires(Robot::camera.get());

	m_shoot = shoot;
}

// Called just before this Command runs the first time
void Viser::Initialize()
{
	Robot::camera->GetInfo();
}

// Called repeatedly when this Command is scheduled to run
void Viser::Execute()
{
	Robot::camera->GetInfo();

	double rotationValue(0);
	double moveValue(0);

	m_continue = false;

	if(std::abs(Camera::distance - distance) > distanceOffset) {
		moveValue = (Camera::distance - distance > 0 ? -1 : 1) * move;
		m_continue = true;
	}

	if(std::abs(Camera::ecart) > offsetX) {
		rotationValue = (Camera::ecart > 0 ? 1 : -1) * rotation;
		m_continue = true;
	}


	Robot::basePilotable->ArcadeDrive(moveValue, rotationValue);


}

// Make this return true when this Command no longer needs to run execute()
bool Viser::IsFinished()
{
	return !m_continue;
}

// Called once after isFinished returns true
void Viser::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Viser::Interrupted()
{

}
