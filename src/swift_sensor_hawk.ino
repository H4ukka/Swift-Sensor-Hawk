/*
    NAME:   Swift Sensor Hawk
    DATE:   25.02.2015  
    VER:    v0r0

    DESC:

        Description goes here.
    

    -----------------------
    Copyright stuff here
    -----------------------
    laine.antti.e@gmail.com

    TODO:
    -
*/

#include "hardware.h"
#include "MasterSensor.h"

MasterSensor SensorMaster (_get_adc);

void setup () {

    Serial.begin(9600);
}

void loop () {

    Serial.println(SensorMaster.measure());
    
}