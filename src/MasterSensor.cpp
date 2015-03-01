#include "MasterSensor.h"


MasterSensor::MasterSensor (function_pointer adcp) { 
	adcp_ = adcp;
	Vector sensor_ports_ ();
}

MasterSensor::~MasterSensor () {

	/**
	*
	* Free up the memory we've used. Stricly not necessary since
	* repowering the device will reset memory; but it's good
	* practice. There should never been a need to reset
	* the MasterSensor class mid-operation.
	*
	**/
	
	sensor_ports_.vec_free ();
}

int MasterSensor::measure () {
    
    return adcp_ (3);
}

void MasterSensor::scan () {

}