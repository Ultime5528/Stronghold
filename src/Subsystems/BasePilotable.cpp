// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "BasePilotable.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "../Commands/Pilotage.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

double BasePilotable::constanteGyro(0);


BasePilotable::BasePilotable() : Subsystem("BasePilotable") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    driveGauche = RobotMap::basePilotabledriveGauche;
    driveDroite = RobotMap::basePilotabledriveDroite;
    drive = RobotMap::basePilotableDrive;
    encoGauche = RobotMap::basePilotableencoGauche;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    gyro = RobotMap::basePilotableGyro;

    m_turning = false;
    m_isGoingRight = false;
    m_setpoint = 0.0;

    gyro->Calibrate();
}

void BasePilotable::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new Pilotage());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void BasePilotable::ArcadeDrive(){
	drive->ArcadeDrive(Robot::oi->getStick().get(), true);

}

void BasePilotable::ArcadeDrive(double avancer, double rotation) {
	drive->ArcadeDrive(avancer, rotation);
}

void BasePilotable::Stop(){
	m_turning = false;
	drive->StopMotor();
}

void BasePilotable::Avancer(){
	 drive->ArcadeDrive(.4, -1 * constanteGyro * gyro->GetAngle());

}

void BasePilotable::GyroReset(){

	gyro->Reset();

}

void BasePilotable::EncoReset(){

	encoGauche->Reset();
}

bool BasePilotable::HasReached(double distance){

	return abs(encoGauche->GetDistance()) >= abs(distance); //&& abs(encoDroite->GetDistance()) >= abs(distance);  && encoDroite->GetDistance() >= distance;


}

bool BasePilotable::HasTurned(){

	if(m_isGoingRight)
		return GetGyroAngle() >= m_setpoint;
	else
		return GetGyroAngle() <= m_setpoint;

}

void BasePilotable::Tourner() {


		if (m_isGoingRight){
				drive->ArcadeDrive(0, .35, false);
		}
		else  {
				drive->ArcadeDrive(0, -.35, false);
		}

}

void BasePilotable::SetSetpoint(double setpoint){
	m_setpoint = setpoint;

	if(setpoint > 0)
		m_isGoingRight = true;
	else
		m_isGoingRight = false;


}

double BasePilotable::GetGyroAngle() {

	return gyro->GetAngle();
}

double BasePilotable::GetEncoGauche() {
	return encoGauche->GetDistance();
}

