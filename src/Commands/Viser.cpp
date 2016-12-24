#include "Viser.h"
#include "Shoot.h"
#include "CSpin.h"
#include "CShoot.h"
#include "../Subsystems/Camera.h"
#include "../Robot.h"
#include <string>

double Viser::TARGET_H(0.2);
double Viser::TARGET_H_OFFSET(0.0);
double Viser::TARGET_X(0.0);
double Viser::TARGET_X_OFFSET(0.0);

double Viser::FORWARD_P(0.0);
double Viser::FORWARD_I(0.0);
double Viser::FORWARD_D(0.0);

double Viser::ROTATE_P(0.0);
double Viser::ROTATE_I(0.0);
double Viser::ROTATE_D(0.0);

Viser::Viser() :
		Command("Viser"),
		forwardPID(nullptr),
		rotatePID(nullptr),
		m_isFinished(false),
		m_hauteur(1.0),
		m_centreX(1.0)
{
	Requires(Robot::basePilotable.get());
	Requires(Robot::camera.get());
	forwardPID.reset(new frc::PIDCalculator(FORWARD_P, FORWARD_I, FORWARD_D));
	rotatePID.reset(new frc::PIDCalculator(ROTATE_P, ROTATE_I, ROTATE_D));

}

// Called just before this Command runs the first time
void Viser::Initialize()
{
	forwardPID->SetPID(FORWARD_P, FORWARD_I, FORWARD_D);
	forwardPID->SetInputRange(0.0, 1.0);
	forwardPID->SetOutputRange(-1.0, 1.0);
	forwardPID->SetSetpoint(TARGET_H);
	forwardPID->Enable();

	rotatePID->SetPID(ROTATE_P, ROTATE_I, ROTATE_D);
	rotatePID->SetInputRange(-1.0, 1.0);
	rotatePID->SetOutputRange(-1.0, 1.0);
	rotatePID->SetSetpoint(TARGET_X);
	rotatePID->Enable();

	Robot::camera->StartThread(&Viser::SetParameters, this);
}

// Called repeatedly when this Command is scheduled to run
void Viser::Execute()
{

	{
		std::unique_lock<std::mutex> lock(m_mutex, std::try_to_lock);

		if(lock.owns_lock()) {
			forwardPID->SetInput(m_hauteur);
			rotatePID->SetInput(m_centreX);

			DriverStation::ReportError("Hauteur : " + std::to_string(m_hauteur));
			DriverStation::ReportError("CentreX : " + std::to_string(m_centreX));
		}
		else {
			forwardPID->Calculate();
			rotatePID->Calculate();
		}
	}

	SmartDashboard::PutNumber("Forward Setpoint", forwardPID->GetSetpoint());

	Robot::basePilotable->ArcadeDrive(forwardPID->Get(), rotatePID->Get());

	SmartDashboard::PutNumber("ForwardPID Get", forwardPID->Get());
	SmartDashboard::PutNumber("RotatePID Get", rotatePID->Get());

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
	return fabs(m_centreX - TARGET_X) < TARGET_X_OFFSET && fabs(m_hauteur - TARGET_H) < TARGET_H_OFFSET;
}

// Called once after isFinished returns true
void Viser::End()
{
	Robot::camera->EndThread();
	forwardPID->Disable();
	rotatePID->Disable();
	DriverStation::ReportError("Fin viser");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Viser::Interrupted()
{
	End();
	DriverStation::ReportError("Viser interrompu");
}

void Viser::SetParameters(double hauteur, double centreX) {
	std::lock_guard<std::mutex> lock(m_mutex);
	m_hauteur = hauteur;
	m_centreX = centreX;
}
