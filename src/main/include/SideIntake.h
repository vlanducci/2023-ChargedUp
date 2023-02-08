#pragma once

#include "Gearbox.h"
#include "behaviour/HasBehaviour.h"
#include <frc/DoubleSolenoid.h>
#include <frc/DigitalInput.h>
#include <networktables/NetworkTableInstance.h>
#include "TOF.h"


struct SideIntakeConfig {
  wom::Gearbox rightMotorGearbox;
  wom::Gearbox leftMotorGearbox;
  frc::DoubleSolenoid *claspSolenoid;
  frc::DoubleSolenoid *deploySolenoid;
  frc::DigitalInput *frontBeamBreak;
  frc::DigitalInput *backBeamBreak;
  TOF *gripperTOF;
};

enum class SideIntakeState {
  kIdle,
  kIntaking,
  kOuttaking,
  kMovePiston,
  kHolding
};

class SideIntake : public behaviour::HasBehaviour {
 public:
  SideIntake(SideIntakeConfig config);

  void OnUpdate(units::second_t dt);

  void SetIdle();
  void SetIntaking(float triggerVal);
  void SetOuttaking(float triggerVal);
  void SetPistons();
  void SetHolding();


  SideIntakeState GetState() const;

 private:
  nt::NetworkTableInstance _ntInstance = nt::NetworkTableInstance::GetDefault();

  SideIntakeConfig _config;
  SideIntakeState _state = SideIntakeState::kIdle;

  units::volt_t manualVoltage = 0_V;
  // units::volt_t intakeVoltage = 7_V;
  // units::volt_t outtakeVoltage = 3_V;
  units::volt_t holdVoltage = 2_V;
  units::volt_t manualIntakeVoltage = 0_V;
  units::volt_t manualOuttakeVoltage = 2_V;
};