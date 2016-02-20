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
    encoDroite = RobotMap::basePilotableencoDroite;
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


void BasePilotable::Stop(){
	drive->ArcadeDrive(0,0, false);
	m_turning = false;
}

void BasePilotable::Avancer(){
	 drive->ArcadeDrive(.2, -1 * constanteGyro * gyro->GetAngle());

}

void BasePilotable::GyroReset(){

	gyro->Reset();

}

void BasePilotable::EncoReset(){

	encoGauche->Reset();
	encoDroite->Reset();
}

bool BasePilotable::HasReached(double distance){

	return encoGauche->GetDistance() >= distance && encoDroite->GetDistance() >= distance;


}

bool BasePilotable::HasTurned(){
	if (m_turning) {
			return m_isGoingRight == (gyro->GetAngle() >= m_setpoint);
		}

		else {
			return (gyro->GetAngle() < m_setpoint + 0.2) && (gyro->GetAngle() > m_setpoint - 0.2);
		}


}

void BasePilotable::Tourner() {

	if(!HasTurned()) {

		m_turning = true;

		if (gyro->GetAngle() > m_setpoint){
			drive->ArcadeDrive(0, .3, false);
			m_isGoingRight = false;
		}
		else  {
			drive->ArcadeDrive(0, -.3, false);
			m_isGoingRight = true;
		}



	}
}

void BasePilotable::SetSetpoint(double setpoint){
	m_setpoint = setpoint;
}

double BasePilotable::GetGyroAngle() {

	return gyro->GetAngle();

}

