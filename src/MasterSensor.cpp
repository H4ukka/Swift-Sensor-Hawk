#include "MasterSensor.h"


MasterSensor::MasterSensor (function_pointer adcp) { 
    adcp_ = adcp;

    for (short i = 0; i < MAX_CHANNELS; i++) {
        sensor_channels_[i] = -1;
    }
}

MasterSensor::~MasterSensor () {
}

int MasterSensor::measure (short channel_index) {
    
    return adcp_ (sensor_channels_[channel_index]);
}

void MasterSensor::scan () {

}

void MasterSensor::addChannel (short channel) {

    for (short i = 0; i < MAX_CHANNELS; i++) {

        if (sensor_channels_[i] == -1) {
            sensor_channels_[i] = channel;
            break;
        }
    }
}

short MasterSensor::getChannelId (short channel_index) {

    return sensor_channels_[channel_index];
}