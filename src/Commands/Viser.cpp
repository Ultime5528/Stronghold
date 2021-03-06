#include "Viser.h"
#include "Shoot.h"
#include "CSpin.h"
#include "CShoot.h"
#include "../Subsystems/Camera.h"
#include "../Robot.h"
#include <cmath>

double Viser::distance(1.8);
double Viser::distanceOffset(0.1);
double Viser::offsetX(0.1);
double Viser::rotation(0.51);
double Viser::move(0.6);


Viser::Viser(bool shoot) : Command("Viser")//, timer()
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

	//timer.Reset();
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
		DriverStation::ReportError("D�but tourne");
		m_rotate = true;

		if(m_shoot)
			Scheduler::GetInstance()->AddCommand(new CSpin(false));
	}

	if(std::abs(Camera::ecart) > offsetX && m_rotate) {
		Robot::basePilotable->ArcadeDrive(0.0, (Camera::ecart > 0 ? 1 : -1.1) * rotation);
		m_continue = true;
	}
	else if(m_rotate) {
			DriverStation::ReportError("Fin tourne");
			m_rotate = false;
			Robot::basePilotable->ArcadeDrive(0.0, 0.0);
		if(m_shoot) {
			Scheduler::GetInstance()->AddCommand(new CShoot(false));
		}

	}

	//Version avec timer
/*
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
			DriverStation::ReportError("D�but tourne");
			m_rotate = true;

			if(!m_firstTime)  {
				Scheduler::GetInstance()->AddCommand(new CSpin(false));
				timer.Reset();
				timer.Start();
			}

		}

		if(std::abs(Camera::ecart) > offsetX && m_rotate) {
			Robot::basePilotable->ArcadeDrive(0.0, (Camera::ecart > 0 ? 1 : -1) * rotation);
			m_continue = true;
		}
		else if(m_rotate && m_firstTime) {

				DriverStation::ReportError("Fin premi�re fois Viser");
				m_firstTime = false;
				m_rotate = false;
				m_continue = true;
		}

		else if(m_rotate && timer.Get() > 1.0){
			DriverStation::ReportError("Fin tourne");
			m_rotate = false;
			Scheduler::GetInstance()->AddCommand(new CShoot(false));
			Robot::basePilotable->ArcadeDrive(0.0, 0.0);
		}

*/
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
	DriverStation::ReportError("Viser interrompu");
}
