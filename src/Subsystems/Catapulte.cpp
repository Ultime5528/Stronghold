// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "Catapulte.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "../Commands/CLoad.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS

double Catapulte::potMax(0);
double Catapulte::potMin(0);
double Catapulte::potShoot(0);

Catapulte::Catapulte() : Subsystem("Catapulte") {
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    shoot = RobotMap::catapulteshoot;
    conv = RobotMap::catapulteconv;
    monte = RobotMap::catapultemonte;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    m_loaded = false;
    m_reaching = false;
    m_isGoingUp = false;
    m_setpoint = false;

}

void Catapulte::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND

        SetDefaultCommand(new CLoad());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

    void Catapulte::SetAtShoot() {
    	m_setpoint = potShoot;
    }
	void Catapulte::SetAtMin() {
		m_setpoint = potMax;
	}
	void Catapulte::Reach() {
		if(!HasReached()) {

			m_reaching = true;

			if (pot->Get() < m_setpoint){
				Down();
				m_isGoingUp = false;
			}
			else  {
				Up();
				m_isGoingUp = true;
			}
		}
		else {
			Maintien();
		}
	}

	void Catapulte::StopConv() {
		conv->Set(0);
	}

	void Catapulte::StopSpin(){
		std::static_pointer_cast<VictorSP>(shoot)->SetSafetyEnabled(true);
		shoot->Set(0);
	}

	void Catapulte::StopMonte(){
		monte->Set(0);
	}

	void Catapulte::ConvToBack() {
		if(!IsLoaded())
			conv->Set(0.14);
	}

	void Catapulte::ConvThrow() {
		conv->Set(-1);
	}

	void Catapulte::SpinToBack() {
		shoot->Set(0.33);
	}

	void Catapulte::Spin() {
		std::static_pointer_cast<VictorSP>(shoot)->SetSafetyEnabled(false);
		shoot->Set(-1);
	}

	void Catapulte::Up() {

		if (pot->Get() >= potMin) {
			monte->Set(0.4);
		}
		else  {
			StopMonte();
		}
	}

	void Catapulte::Down()
	{
		if (pot->Get() <= potMax) {
			monte->Set(-0.1);
		}
		else  {
			StopMonte();
		}
	}

	void Catapulte::StopMonte() {
		monte->Set(0);
			m_reaching = false;
	}

	void Catapulte::Maintien() {
		if(pot->Get() > potMin)
			monte->Set(0.1);
	}

	bool Catapulte::HasReached() {
		if (m_reaching) {
				bool doneReaching;
				doneReaching = (m_isGoingUp == (pot->Get() <= m_setpoint));
				if (doneReaching)
					m_reaching = false;
				return doneReaching;
			}

			else {
				return (pot->Get() < m_setpoint + 0.004) && (pot->Get() > m_setpoint - 0.004);
			}

	}

	bool Catapulte::IsLoaded(){
		return limit->Get();
	}

// Put methods for controlling this subsystem
// here. Call these from Commands.

