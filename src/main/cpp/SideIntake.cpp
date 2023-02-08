#include "SideIntake.h"
#include <units/length.h>

using namespace frc;
using namespace wom;

SideIntake::SideIntake(SideIntakeConfig config) : _config(config) {}

void SideIntake::OnUpdate(units::second_t dt) {
  units::volt_t voltage = 0_V;

  switch (_state) {
    case SideIntakeState::kIdle:
      voltage = 0_V;
      _config.claspSolenoid->Set(frc::DoubleSolenoid::kReverse);
      break;

    case SideIntakeState::kIntaking:
      if ((_config.frontBeamBreak->Get()) && (_config.backBeamBreak->Get())) {
        _state = SideIntakeState::kHolding;
      } else {
        _ntInstance.GetTable("sideIntake")->GetEntry("One or no sensor detecting object in intake").SetDouble(0.0);
        voltage = manualIntakeVoltage;
      }
      break;

    case SideIntakeState::kMovePiston:
      _config.deploySolenoid->Toggle();
      break;

    case SideIntakeState::kOuttaking:
      voltage = manualOuttakeVoltage;
      break;

    case SideIntakeState::kHolding:
      if ((!_config.backBeamBreak->Get()) && (!_config.backBeamBreak->Get()) && (_config.gripperTOF->GetDistance() > 5_m)) {  // tune this 
        _state = SideIntakeState::kIdle;
      } else {
        voltage = holdVoltage;
      }
      break;
  }
    _config.leftMotorGearbox.transmission->SetVoltage(voltage);
    _config.leftMotorGearbox.transmission->SetVoltage(voltage);
};

void SideIntake::SetIdle() {
  _state = SideIntakeState::kIdle;
}

void SideIntake::SetIntaking(float triggerVal) {
  _state = SideIntakeState::kIntaking;
  manualIntakeVoltage = triggerVal * 6_V;
}

void SideIntake::SetOuttaking(float triggerVal) {
  _state = SideIntakeState::kOuttaking;
  manualOuttakeVoltage = triggerVal * -4_V;
}

void SideIntake::SetPistons() {
  _state = SideIntakeState::kMovePiston;
}

void SideIntake::SetHolding() {
  _state = SideIntakeState::kHolding;
}

SideIntakeState SideIntake::GetState() const {
  return _state;
}