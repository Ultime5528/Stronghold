// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef BASEPILOTABLE_H
#define BASEPILOTABLE_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class BasePilotable: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<SpeedController> driveGauche;
	std::shared_ptr<SpeedController> driveDroite;
	std::shared_ptr<RobotDrive> drive;
	std::shared_ptr<Encoder> encoGauche;
	std::shared_ptr<Encoder> encoDroite;
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<AnalogGyro> gyro;

	bool m_isGoingRight;
	bool m_turning;
	double m_setpoint;

public:
	static double constanteGyro;


	BasePilotable();
	void InitDefaultCommand();
	void ArcadeDrive();
	void Stop();
	void Avancer();
	void GyroReset();
	void EncoReset();
	bool HasReached(double distance);
	void Tourner();
	bool HasTurned();
	void SetSetpoint(double setpoint);


	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTANTS
};

#endif
