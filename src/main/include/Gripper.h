#pragma once

#include "Gearbox.h"
#include "behaviour/HasBehaviour.h"
#include <ctre/Phoenix.h>

struct GripperConfig {
  wom::MotorVoltageController *rightGripperMotor;
  wom::MotorVoltageController *leftGripperMotor;
};

enum class GripperState {
  kIdle,
  kIntaking,
  kOuttaking
};

enum class GamePieceType {
  kCube,
  kCone
};

class Gripper : public behaviour::HasBehaviour {
 public:
  Gripper(GripperConfig &config);
  
  void OnUpdate(units::second_t dt);

  void SetIdle();
  void SetIntaking(GamePieceType gpt);
  void SetOuttaking(GamePieceType gpt);

 private:
  GripperState _state = GripperState::kIdle;
  GamePieceType _gamePieceType;
  GripperConfig &_config;

  units::volt_t coneIntakeVoltage = 10_V;
  units::volt_t coneOuttakeVoltage = -7_V;
  units::volt_t cubeIntakeVoltage = 10_V;
  units::volt_t cubeOuttakeVoltage = -7_V;
  units::volt_t holdVoltage = 2_V;
};