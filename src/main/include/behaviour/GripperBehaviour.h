#pragma once

#include <frc/XboxController.h>
#include "behaviour/Behaviour.h"
#include "Gripper.h"

class GripperManualBehaviour : public behaviour::Behaviour {
 public: 
  GripperManualBehaviour(Gripper *gripper, frc::XboxController &codriver);

  void OnStart() override;
  void OnTick(units::second_t dt) override;

 private:
  Gripper *_gripper;
  frc::XboxController &_codriver;
};