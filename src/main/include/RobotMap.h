#pragma once

#include "Intake.h"
#include "TestClimber.h"
#include "VoltageController.h"
#include "DCMotor.h"
#include <frc/XboxController.h>
#include <ctre/Phoenix.h>

struct RobotMap {
  struct Controllers {
    frc::XboxController driver{0};
  };
  Controllers controllers;

  /**
   * Resources and Paramters related to the Intake Subsystem
   */
  struct IntakeSystem {
    /* Create a new Voltage Controller */
    wom::MotorVoltageController controller{new WPI_TalonSRX(10)};
    
    wom::Gearbox gearbox{
      &controller,
      nullptr,  /* nullptr for encoder means we have no encoder */
      wom::DCMotor::Bag(1).WithReduction(1) /* TODO: Update this reduction */
    };

    /* The beambreak sensor on Digital Channel 0 */
    frc::DigitalInput sensor{0};

    /* Create the intake config with the given resources */
    IntakeConfig config{
      gearbox,
      &sensor
    };
  };
  IntakeSystem intake;

  struct TestClimberSystem {
    // creating motors / motor controllers 
    wom::MotorVoltageController motor1{new WPI_TalonSRX(999)};
    wom::MotorVoltageController motor2{new WPI_TalonSRX(999)};
    // or
    TalonSRX motor3{999};
    TalonSRX motor4{999};
    // or create group of motors
    wom::MotorVoltageController motor = wom::MotorVoltageController::Group(motor3, motor4);

    // create solenoid
    

    // create encoder
    wom::DigitalEncoder encoder{0, 1, 2048};

    // create beambreak sensor
    frc::DigitalInput sensor{999};

    wom::Gearbox testClimberGearbox{
      &motor1, 
      nullptr,  /* nullptr for encoder means we have no encoder */
      wom::DCMotor::Bag(1).WithReduction(1) /* TODO: Update this reduction */
    };
  };
  TestClimberSystem testClimber;
  
};