#include "Robot.h"

#include "behaviour/BehaviourScheduler.h"
#include "behaviour/Behaviour.h"
#include "behaviour/SwerveBaseBehaviour.h"
#include "behaviour/SideIntakeBehaviour.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/event/BooleanEvent.h>
#include <networktables/NetworkTableInstance.h>

using namespace frc;
using namespace behaviour;

static units::second_t lastPeriodic;

void Robot::RobotInit() {
  lastPeriodic = wom::now();

  armavator = new Armavator(map.armavator.config);
  BehaviourScheduler::GetInstance()->Register(armavator);

  sideIntake = new SideIntake(map.sideIntake.config);
  BehaviourScheduler::GetInstance()->Register(sideIntake);
  sideIntake->SetDefaultBehaviour([this]() {
    return make<SideIntakeBehaviour>(sideIntake, map.controllers.codriver);
  });
  
  swerve = new wom::SwerveDrive(map.swerveBase.config, frc::Pose2d());
  BehaviourScheduler::GetInstance()->Register(swerve);
  swerve->SetDefaultBehaviour([this]() {
    return make<ManualDrivebase>(swerve, &map.controllers.driver);
  });

}

void Robot::RobotPeriodic() {
  auto dt = wom::now() - lastPeriodic;
  lastPeriodic = wom::now();
  
  loop.Poll();
  BehaviourScheduler::GetInstance()->Tick();

  armavator->OnUpdate(dt);
  swerve->OnUpdate(dt);
  sideIntake->OnUpdate(dt);

  // std::optional<units::meter_t> distance = map.gripper.gamepiecePresence.GetDistance();
  // if (distance.has_value())
  //   nt::NetworkTableInstance::GetDefault().GetTable("TOF")->GetEntry("distance").SetDouble(distance.value().value());
  // else
  //   nt::NetworkTableInstance::GetDefault().GetTable("TOF")->GetEntry("distance").SetDouble(-1);
}

void Robot::AutonomousInit() { }
void Robot::AutonomousPeriodic() { }

void Robot::TeleopInit() {
  loop.Clear();
  BehaviourScheduler *sched = BehaviourScheduler::GetInstance();
  
  // map.controllers.driver.A(&loop).Rising().IfHigh([sched, this]() {
  //   sched->Schedule(make<ArmavatorGoToPositionBehaviour>(armavator, ArmavatorPosition{0.2_m, 0_deg}));
  // });

  // map.controllers.driver.B(&loop).Rising().IfHigh([sched, this]() {
  //   sched->Schedule(make<ArmavatorGoToPositionBehaviour>(armavator, ArmavatorPosition{1.2_m, -75_deg}));
  // });

  // map.controllers.driver.X(&loop).Rising().IfHigh([sched, this]() {
  //   sched->Schedule(make<ArmavatorGoToPositionBehaviour>(armavator, ArmavatorPosition{1.0_m, 240_deg}));
  // });

  // map.controllers.driver.Y(&loop).Rising().IfHigh([sched, this]() {
  //   sched->Schedule(make<ArmavatorGoToPositionBehaviour>(armavator, ArmavatorPosition{0_m, 0_deg}));
  // });

  // map.controllers.driver.POV(0, &loop).Rising().IfHigh([sched, this]() { // up dpad
  //   sched->Schedule(make<DrivebasePoseBehaviour>(swerve, frc::Pose2d(1_m, 1_m, 0_rad)));
  // });

}

void Robot::TeleopPeriodic() {}

void Robot::DisabledInit() { }
void Robot::DisabledPeriodic() { }

void Robot::TestInit() { }
void Robot::TestPeriodic() { }

/* SIMULATION */

#include <frc/simulation/BatterySim.h>
#include <frc/simulation/RoboRioSim.h>
#include <networktables/NetworkTableInstance.h>
#include "ControlUtil.h"

static units::second_t lastSimPeriodic{0};
static auto simTable = nt::NetworkTableInstance::GetDefault().GetTable("/sim");

struct SimConfig {
  ::sim::ArmavatorSim arm;
  wom::sim::SwerveDriveSim swerveSim; 
};
SimConfig *simConfig;

void Robot::SimulationInit() {
  simConfig = new SimConfig{
    ::sim::ArmavatorSim(map.armavator.config),
    wom::sim::SwerveDriveSim(map.swerveBase.config, 0.5 * 6_lb * 7.5_in * 7.5_in)
  };

  lastSimPeriodic = wom::now();
}

void Robot::SimulationPeriodic() {
  auto dt = wom::now() - lastSimPeriodic;

  simConfig->arm.OnUpdate(dt);
  simConfig->swerveSim.Update(dt);

  auto batteryVoltage = units::math::min(units::math::max(frc::sim::BatterySim::Calculate({
    simConfig->arm.GetCurrent(),
  }), 0_V), 12_V);
  frc::sim::RoboRioSim::SetVInVoltage(batteryVoltage);
  simTable->GetEntry("batteryVoltage").SetDouble(batteryVoltage.value()); 

  lastSimPeriodic = wom::now();
}