#include "MasterSensor.h"

MasterSensor::MasterSensor (FP adcp) { _adcp = adcp;}

int MasterSensor::measure () {
    
    return _adcp(3);
}