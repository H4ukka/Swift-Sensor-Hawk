#include "MasterSensor.h"

MasterSensor::MasterSensor (function_pointer adcp) { adcp_ = adcp;}

int MasterSensor::measure () {
    
    return adcp_(3);
}