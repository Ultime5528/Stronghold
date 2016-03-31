#include "AutomaticCapture.h"

AutomaticCapture::AutomaticCapture() : Command("AutomaticCapture")
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires (Robot::camera.get());
}

// Called just before this Command runs the first time
void AutomaticCapture::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void AutomaticCapture::Execute()
{
	Robot::camera->SendImage();
	//Robot::camera->GetInfo();
}

// Make this return true when this Command no longer needs to run execute()
bool AutomaticCapture::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void AutomaticCapture::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutomaticCapture::Interrupted()
{
	End();
}
