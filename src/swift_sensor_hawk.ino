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

#include "MasterSensor.h"
#include "hardware.h"

MasterSensor SensorMaster (g_get_adc);

void setup () {

    Serial.begin(9600);
}

void loop () {

    Serial.println(SensorMaster.measure());
    
}