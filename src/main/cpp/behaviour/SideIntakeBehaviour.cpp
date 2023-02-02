#include "behaviour/SideIntakeBehaviour.h"

#include <iostream>

SideIntakeBehaviour::SideIntakeBehaviour(SideIntake *sideIntake, frc::XboxController &codriver): sideIntake(sideIntake), _codriver(codriver) {
  Controls(sideIntake);
}

void SideIntakeBehaviour::OnStart() {}

void SideIntakeBehaviour::OnTick(units::second_t dt) {
  if (_codriver.GetLeftY()>0.15) {
    sideIntake->SetIntaking(_codriver.GetLeftY());
  sideIntake->SetIntaking(_codriver.GetLeftY());
  // if (_codriver.GetRightBumper()) {
  //   sideIntake->SetOuttaking(_codriver.GetLeftY());
  } else if (_codriver.GetAButton()) {
    sideIntake->SetPistons();
  } else {
    sideIntake->SetIdle();
  }
}