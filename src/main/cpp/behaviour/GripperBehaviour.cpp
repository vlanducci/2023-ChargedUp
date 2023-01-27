#include "behaviour/GripperBehaviour.h"

GripperManualBehaviour::GripperManualBehaviour(Gripper *gripper, frc::XboxController &codriver) : _gripper(gripper), _codriver(codriver) {
  Controls(gripper);
};

void GripperManualBehaviour::OnStart() {}

void GripperManualBehaviour::OnTick(units::second_t dt) {
  if (_codriver.GetAButton()) {
    _gripper->SetIntaking(GamePieceType::kCone);
  } else if (_codriver.GetBButton()) {
    _gripper->SetIntaking(GamePieceType::kCube);
  } else if (_codriver.GetXButton()) {
    _gripper->SetOuttaking(GamePieceType::kCone);
  } else if (_codriver.GetYButton()) {
    _gripper->SetOuttaking(GamePieceType::kCube);
  } else {
    _gripper->SetIdle();
  }
}