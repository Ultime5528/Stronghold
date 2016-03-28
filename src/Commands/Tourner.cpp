// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Tourner.h"
#include "CSpin.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

Tourner::Tourner(double angle, bool shoot): Command("Tourner") {
    m_angle = angle;
    m_shoot = shoot;
	Requires(Robot::basePilotable.get());
}


// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void Tourner::Initialize() {
	Robot::basePilotable->GyroReset();
	Robot::basePilotable->SetSetpoint(m_angle);
}

// Called repeatedly when this Command is scheduled to run
void Tourner::Execute() {
	if(m_angle - Robot::basePilotable->GetGyroAngle() > 0) {
		Robot::basePilotable->ArcadeDrive(0, 0.6);
	}
	else if (m_angle - Robot::basePilotable->GetGyroAngle() < 0) {
		Robot::basePilotable->ArcadeDrive(0, -0.6);
	}

}

// Make this return true when this Command no longer needs to run execute()
bool Tourner::IsFinished() {
    return abs(Robot::basePilotable->GetGyroAngle() - m_angle) < 5;
}

// Called once after isFinished returns true
void Tourner::End() {
	Robot::basePilotable->Stop();
	DriverStation::ReportError("Fin Tourner");

	if(m_shoot)
		Scheduler::GetInstance()->AddCommand(new CSpin());

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Tourner::Interrupted() {
	End();

}
