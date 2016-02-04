// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/Autonomous.h"
#include "Commands/Avancer.h"
#include "Commands/BBasArriere.h"
#include "Commands/BBasAvant.h"
#include "Commands/BDescendArriere.h"
#include "Commands/BDescendAvant.h"
#include "Commands/BGateAvant.h"
#include "Commands/BHautArriere.h"
#include "Commands/BHautAvant.h"
#include "Commands/BLoadArriere.h"
#include "Commands/BLoadAvant.h"
#include "Commands/BMonteArriere.h"
#include "Commands/BMonteAvant.h"
#include "Commands/BSpinArriere.h"
#include "Commands/BSpinAvant.h"
#include "Commands/BSpinInverseAvant.h"
#include "Commands/BUnloadAvant.h"
#include "Commands/CLoad.h"
#include "Commands/CShoot.h"
#include "Commands/CUnload.h"
#include "Commands/PMonte.h"
#include "Commands/PMonteDroite.h"
#include "Commands/PMonteGauche.h"
#include "Commands/PRetract.h"
#include "Commands/Pilotage.h"
#include "Commands/Tourner.h"
#include "Commands/Unload.h"

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    stick.reset(new Joystick(0));
    

    // SmartDashboard Buttons
    SmartDashboard::PutData("Autonomous", new Autonomous());
    SmartDashboard::PutData("Unload", new Unload());
    SmartDashboard::PutData("BSpinArriere", new BSpinArriere());
    SmartDashboard::PutData("BSpinInverseAvant", new BSpinInverseAvant());
    SmartDashboard::PutData("BSpinAvant", new BSpinAvant());
    SmartDashboard::PutData("Tourner", new Tourner());
    SmartDashboard::PutData("Avancer", new Avancer());
    SmartDashboard::PutData("Pilotage", new Pilotage());
    SmartDashboard::PutData("PRetract", new PRetract());
    SmartDashboard::PutData("PMonteDroite", new PMonteDroite());
    SmartDashboard::PutData("PMonteGauche", new PMonteGauche());
    SmartDashboard::PutData("PMonte", new PMonte());
    SmartDashboard::PutData("BDescendArriere", new BDescendArriere());
    SmartDashboard::PutData("BMonteArriere", new BMonteArriere());
    SmartDashboard::PutData("BBasArriere", new BBasArriere());
    SmartDashboard::PutData("BHautArriere", new BHautArriere());
    SmartDashboard::PutData("BDescendAvant", new BDescendAvant());
    SmartDashboard::PutData("BMonteAvant", new BMonteAvant());
    SmartDashboard::PutData("BUnloadAvant", new BUnloadAvant());
    SmartDashboard::PutData("BBasAvant", new BBasAvant());
    SmartDashboard::PutData("BHautAvant", new BHautAvant());
    SmartDashboard::PutData("CShoot", new CShoot());
    SmartDashboard::PutData("CUnload", new CUnload());
    SmartDashboard::PutData("CLoad", new CLoad());
    SmartDashboard::PutData("BLoadAvant", new BLoadAvant());
    SmartDashboard::PutData("BGateAvant", new BGateAvant());
    SmartDashboard::PutData("BLoadArriere", new BLoadArriere());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS


    button1.reset(new JoystickButton(1));
    button2.reset(new JoystickButton(2));
    button3.reset(new JoystickButton(3));
    button4.reset(new JoystickButton(4));

    button1->WhileHeld(new BMonteAvant());
    button2->WhileHeld(new BDescendAvant());
    button3->WhileHeld(new BMonteArriere());
    button4->WhileHeld(new BDescendArriere());


}

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS

std::shared_ptr<Joystick> OI::getStick() {
   return stick;
}

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS