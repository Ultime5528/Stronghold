#include "Viser.h"
#include "Shoot.h"
#include "CSpin.h"
#include "CShoot.h"
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
	m_rotate = false;

}

// Called repeatedly when this Command is scheduled to run
void Viser::Execute()
{
	Robot::camera->GetInfo();


	m_continue = false;

	if(std::abs(Camera::distance - distance) > distanceOffset && !m_rotate) {

		double tourner = 0;

		if(std::abs(Camera::ecart) > offsetX) {
				tourner = (Camera::ecart > 0 ? 1 : -1) * rotation;
		}

		Robot::basePilotable->ArcadeDrive(((Camera::distance - distance) > 0 ? -1 : 1) * move, tourner);
		m_continue = true;
	}
	else if(!m_rotate) {
		DriverStation::ReportError("Début tourne");
		m_rotate = true;
		Scheduler::GetInstance()->AddCommand(new CSpin(false));
	}

	if(std::abs(Camera::ecart) > offsetX && m_rotate) {
		Robot::basePilotable->ArcadeDrive(0.0, (Camera::ecart > 0 ? 1 : -1) * rotation);
		m_continue = true;
	}
	else if(m_rotate) {


		DriverStation::ReportError("Fin tourne");
		m_rotate = false;
		Scheduler::GetInstance()->AddCommand(new CShoot(false));
		Robot::basePilotable->ArcadeDrive(0.0, 0.0);
	}

}

// Make this return true when this Command no longer needs to run execute()
bool Viser::IsFinished()
{
	return !m_continue;
}

// Called once after isFinished returns true
void Viser::End()
{
	DriverStation::ReportError("Fin viser");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Viser::Interrupted()
{

}
