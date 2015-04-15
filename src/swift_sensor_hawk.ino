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

#include <UTFT.h>

#include "colors.h"
#include "ScreenDrawer.h"
#include "MasterSensor.h"
#include "hardware.h"

UTFT LCD0_(CTE32W,38,39,40,41);


MasterSensor SensorMaster (g_get_adc);
ScreenDrawer Screen0;
ScreenDrawer Screen1;
ScreenDrawer Screen2;

void setup () {

    analogReference(INTERNAL2V56);

    LCD0_.InitLCD();

    SensorMaster.addChannel(3);
    SensorMaster.addChannel(4);
    SensorMaster.addChannel(5);

    Screen0.draw_panel ("MAIN_GRAPH");

    Screen0.set_color(DEFAULT_RED);
    // Screen1.set_color(DEFAULT_GREEN);
    // Screen2.set_color(DEFAULT_YELLOW);
}

void loop () {

    // Screen0.draw_graph(map(SensorMaster.measure(0),0,1023,118,0));
    Screen0.draw_graph(SensorMaster.measure(0)-434);
    Screen0.draw_sensor_box (20,140,SensorMaster.measure(0));
    Screen0.step_forward();

    // Screen1.draw_graph(map(SensorMaster.measure(0),0,1023,0,118));
    // Screen1.draw_sensor_box (140,140,map(SensorMaster.measure(0),0,1023,0,118));
    // Screen1.step_forward();

    // Screen2.draw_graph(map(SensorMaster.measure(2),0,1023,0,118));
    // Screen2.draw_sensor_box (260,140,map(SensorMaster.measure(2),0,1023,0,118));
    // Screen2.step_forward();
}