#include "Analyse.h"

Analyse::Analyse()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(Robot::camera.get());
}

// Called just before this Command runs the first time
void Analyse::Initialize()
{
	Robot::camera->StartAnalyse();
	Robot::camera->GetInfo();
}

// Called repeatedly when this Command is scheduled to run
void Analyse::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool Analyse::IsFinished()
{
	return Robot::camera->HasAnalysed();
}

// Called once after isFinished returns true
void Analyse::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Analyse::Interrupted()
{

}
