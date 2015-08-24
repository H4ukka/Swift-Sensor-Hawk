#include "MasterSensor.h"
#include "colors.h"

MasterSensor::MasterSensor (function_pointer adcp) { 
    adcp_ = adcp;
    next_free_channel_ = 0;
}

MasterSensor::~MasterSensor () {
}

bool MasterSensor::measure (short channel_index) {

    short ch_value = adcp_ (channels_[channel_index].id);
    
    channels_[channel_index].value = ch_value;

    return false;
}

void MasterSensor::scan () {

}

void MasterSensor::addChannel (short channel, short r, short g, short b) {

    if (next_free_channel_ < MAX_CHANNELS) {

        channels_ [next_free_channel_].id = channel;

        channels_ [next_free_channel_].R = r;
        channels_ [next_free_channel_].G = g;
        channels_ [next_free_channel_].B = b;

        channels_ [next_free_channel_].prev_X = 0;
        channels_ [next_free_channel_].prev_Y = 0;

        channels_ [next_free_channel_].total = 0;
        channels_ [next_free_channel_].count = 0;

        channels_ [next_free_channel_].limit = 100;
        channels_ [next_free_channel_].min = 10000;
        channels_ [next_free_channel_].max = 0;

        channels_ [next_free_channel_].multiplier = 1;
        channels_ [next_free_channel_].offset = 0;

        next_free_channel_ ++;
    }
}

void MasterSensor::setChannelColor (short channel_index, short r, short g, short b) {

    channels_ [channel_index].R = r;
    channels_ [channel_index].G = g;
    channels_ [channel_index].B = b;
}

void MasterSensor::setLimit (short channel_index, short new_limit) {
    channels_ [channel_index].limit = new_limit;
}

void MasterSensor::setMultiplier (short channel_index, float multiplier) {
    channels_ [channel_index].multiplier = multiplier;
}

Channel* MasterSensor::getChannel (short channel_index) {

    return &channels_ [channel_index];
}

float MasterSensor::convertd (short channel_index) {
    return (channels_ [channel_index].offset - channels_ [channel_index].value) * channels_ [channel_index].multiplier;
}