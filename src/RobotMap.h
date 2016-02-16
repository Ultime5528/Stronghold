// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef ROBOTMAP_H
#define ROBOTMAP_H
#include "WPILib.h"


/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
class RobotMap {
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static std::shared_ptr<SpeedController> catapulteshoot;

	static std::shared_ptr<SpeedController> bouffeurAvantspin;
	static std::shared_ptr<SpeedController> bouffeurAvantmonte;
	static std::shared_ptr<AnalogPotentiometer> bouffeurAvantpot;
	static std::shared_ptr<SpeedController> bouffeurArrierespin;
	static std::shared_ptr<SpeedController> bouffeurArrieremonte;
	static std::shared_ptr<AnalogPotentiometer> bouffeurArrierepot;
	static std::shared_ptr<DoubleSolenoid> rouesPivotpistonGauche;
	static std::shared_ptr<DoubleSolenoid> rouesPivotpistonDroit;
	static std::shared_ptr<SpeedController> basePilotabledriveGauche;
	static std::shared_ptr<SpeedController> basePilotabledriveDroite;
	static std::shared_ptr<RobotDrive> basePilotableDrive;
	static std::shared_ptr<Encoder> basePilotableencoGauche;
	static std::shared_ptr<Encoder> basePilotableencoDroite;

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	static std::shared_ptr<SpeedController> catapulteconv;
	static std::shared_ptr<SpeedController> catapultemonte;
	static std::shared_ptr<AnalogPotentiometer> catapultepot;
	//static std::shared_ptr<ADXRS450_Gyro> basePilotableGyro;
	static std::shared_ptr<USBCamera> cameraCam;

	static void init();
};
#endif
