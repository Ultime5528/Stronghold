#include "Viser.h"
#include "Shoot.h"
#include "CSpin.h"
#include "CShoot.h"
#include "../Subsystems/Camera.h"
#include "../Robot.h"

double Viser::TARGET_H(0.0);
double Viser::TARGET_H_OFFSET(0.0);
double Viser::TARGET_X(0.0);
double Viser::TARGET_X_OFFSET(0.0);

double Viser::FORWARD_P(0.0);
double Viser::FORWARD_I(0.0);
double Viser::FORWARD_D(0.0);

double Viser::ROTATE_P(0.0);
double Viser::ROTATE_I(0.0);
double Viser::ROTATE_D(0.0);

Viser::Viser(bool shoot) :
		Command("Viser"),
		forwardPID(nullptr),
		rotatePID(nullptr),
		m_finished(false)
{
	//Requires(Robot::basePilotable.get());
	Requires(Robot::camera.get());

}

// Called just before this Command runs the first time
void Viser::Initialize()
{
	Robot::camera->StartThread();
}

// Called repeatedly when this Command is scheduled to run
void Viser::Execute()
{



	///Code de l'an passé
	/*
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

	*/

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
			DriverStation::ReportError("Début tourne");
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

				DriverStation::ReportError("Fin première fois Viser");
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
	return m_finished;
}

// Called once after isFinished returns true
void Viser::End()
{
	Robot::camera->EndThread();
	DriverStation::ReportError("Fin viser");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Viser::Interrupted()
{
	Robot::camera->EndThread();
	DriverStation::ReportError("Viser interrompu");
}
