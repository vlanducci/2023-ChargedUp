#pragma once

#include "Gearbox.h"
#include "behaviour/HasBehaviour.h"
#include "RobotMap.h"
#include <frc/DoubleSolenoid.h>


struct SideIntakeConfig {
  wom::Gearbox gearbox;
  frc::DoubleSolenoid *solenoid1;
  frc::DoubleSolenoid *solenoid2;
};

enum class SideIntakeState {
  kIdle,
  kIntaking,
  kGrabPiston,
  kMovePiston,
  kOuttaking
};

class SideIntake : public behaviour::HasBehaviour {
 public:
  SideIntake(SideIntakeConfig config);

  void OnUpdate(units::second_t dt);

  void SetIntaking();
  void SetPistons();
  void SetOuttaking();

  SideIntakeState GetState() const;

 private:
  SideIntakeConfig _config;
  SideIntakeState _state = SideIntakeState::kIdle;

  units::volt_t intakeVoltage = 10_V;
  units::volt_t outtakeVoltage = -7_V;
  units::volt_t holdVoltage = 2_V;
};