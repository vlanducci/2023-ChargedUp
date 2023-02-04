#pragma once

#include <frc/XboxController.h>
#include "behaviour/Behaviour.h"
#include "Armavator.h"
#include "Grid.h"
#include <units/angle.h>
#include <units/length.h>
#include <iostream>

class ArmavatorGoToPositionBehaviour : public behaviour::Behaviour {
 public:
   using grid_t = ArmavatorConfig::grid_t;

   //constructor for class
   ArmavatorGoToPositionBehaviour(Armavator *armavator, ArmavatorPosition setpoint);

   //Override the OnStart abd OnTick functions, while setting the units for when Armavator runs
   void OnStart() override;
   void OnTick(units::second_t dt) override;

 private:
   //stores nessesary information that can't be changed
   Armavator *_armavator;

   ArmavatorPosition _setpoint;
   std::deque<grid_t::GridPathNode<units::second>> _waypoints;
};

// class ArmavatorManualBehaviour : public behaviour::Behaviour {
//  public:
//   using grid_t = ArmavatorConfig::grid_t;

//   ArmavatorManualBehaviour(Armavator *armavator, frc::XboxController &codriver);

//   void OnStart() override;
//   void OnTick(units::second_t dt) override;
//  private:
//   Armavator *_armavator;

//   ArmavatorPosition _setpoint;
//   std::deque<grid_t::GridPathNode<units::second>> _waypoints;
//   frc::XboxController &_codriver;
// };

class ArmavatorRawBehaviour : public behaviour::Behaviour {
 public:
  using grid_t = ArmavatorConfig::grid_t;

  //constructor
  ArmavatorRawBehaviour(Armavator *armavator, frc::XboxController &codriver);

  units::radian_t getCorrectAngle(units::meters height = 0_meter) {
    if (height < 0.28_m) {
      _setpoint.angle == 0_deg;
    } else {
      if (height => 0.28_meter && height < 0.88) {
        _setpoint.angle => 0_deg && _setpoint.angle < 90_deg;
      } else if (height => 0.88_meter && height < 1.18) {
        _setpoint.angle => -45_deg && _setpoint.angle < 90_deg;
      } else if (height => 1.18_meter && height < 1.33) {
        _setpoint.angle => -45_deg && _setpoint.angle < 180_deg;
      } else if (height == 1.33) {
        _setpoint.angle => -90_deg && _setpoint.angle < 270_deg;
      }
    }
    return _setpoint.angle;
  }

  void OnStart() override;
  void OnTick(units::second_t dt) override;
 private:
  Armavator *_armavator;

  ArmavatorPosition _setpoint;
  std::deque<grid_t::GridPathNode<units::second>> _waypoints;
  frc::XboxController &_codriver;
};