#include "Gripper.h"

using namespace frc;
using namespace wom;

Gripper::Gripper(GripperConfig &config) : _config(config) {}

void Gripper::OnUpdate(units::second_t dt) {
  units::volt_t voltage = 0_V;

  switch(_state) {
    case GripperState::kIdle:
      break;

    case GripperState::kIntaking:
      if (_config.gamepiecePresence->GetDistance() > 5_m) {
        _state = GripperState::kHolding;
      } else {
        if (_gamePieceType == GamePieceType::kCone) {
          voltage = coneIntakeVoltage;
        } else {
          voltage = cubeIntakeVoltage;
        }
      } break;

    case GripperState::kHolding:
      voltage = holdVoltage;
      break;

    case GripperState::kOuttaking:
      if (_gamePieceType == GamePieceType::kCone) {
        voltage = coneOuttakeVoltage;
      } else {
        voltage = cubeOuttakeVoltage;
      } break;
  }
  _config.leftGripperMotor->SetVoltage(voltage);
  _config.rightGripperMotor->SetVoltage(voltage);
}

void Gripper::SetIdle() {
  _state = GripperState::kIdle;
}

void Gripper::SetIntaking(GamePieceType gpt) {
  _state = GripperState::kIntaking;
}

void Gripper::SetOuttaking(GamePieceType gpt) {
  _state = GripperState::kOuttaking;
}

void Gripper::SetHolding() {
  _state = GripperState::kHolding;
}