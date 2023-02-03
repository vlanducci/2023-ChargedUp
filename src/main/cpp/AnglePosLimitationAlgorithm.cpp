#include "Armavator.h"
#include "Armavator.cpp"

if(setpoint.height < 0.28_meter) {
  setpoint.angle == 0_deg;
} else {
  if(setpoint.height => 0.28_meter && setpoint.height < 0.88) {
    setpoint.angle => 0_deg && setpoint.angle < 90_deg;
  } else if(setpoint.height => 0.88_meter && setpoint.height < 1.18) {
    setpoint.angle => -45_deg && setpoint.angle < 90_deg;
  } else if(setpoint.height => 1.18_meter && setpoint.height < 1.33) {
    setpoint.angle => -45_deg && setpoint.angle < 180_deg;
  }if(setpoint.height == 1.33) {
    setpoint.angle => -90_deg && setpoint.angle < 270_deg;
  }
}