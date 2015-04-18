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
#include <SPI.h>
#include <SD.h>

#include "colors.h"
#include "ScreenDrawer.h"
#include "MasterSensor.h"
#include "hardware.h"

UTFT LCD0_(CTE32W,38,39,40,41);


MasterSensor SensorMaster (g_get_adc);
ScreenDrawer Screen0;
ScreenDrawer Screen1;
ScreenDrawer Screen2;

const int chipSelect = 53;

void setup () {

<<<<<<< HEAD
    //analogReference(INTERNAL2V56);

    Serial.begin(9600);
=======
    analogReference(INTERNAL2V56);
>>>>>>> origin/master

    LCD0_.InitLCD();

    SensorMaster.addChannel(3);
    SensorMaster.addChannel(4);
    SensorMaster.addChannel(5);

    Screen0.draw_panel ("MAIN_GRAPH");

    Screen0.set_color(DEFAULT_RED);
    // Screen1.set_color(DEFAULT_GREEN);
    // Screen2.set_color(DEFAULT_YELLOW);
<<<<<<< HEAD
    //Serial.print("Initializing SD card...");

    // // see if the card is present and can be initialized:
    // if (!SD.begin(chipSelect)) {
    //     Serial.println("Card failed, or not present");
    //     // don't do anything more:
    //     return;
    // }
    // Serial.println("card initialized.");
=======
>>>>>>> origin/master
}

void loop () {

    // Screen0.draw_graph(map(SensorMaster.measure(0),0,1023,118,0));
    Screen0.draw_graph(120-(SensorMaster.measure(0)-380));
    Screen0.draw_sensor_box (20,140,(502 - SensorMaster.measure(0))*1.494);
    Screen0.draw_sensor_box (160,140,SensorMaster.measure(0));
    Screen0.step_forward();

    // Screen1.draw_graph(map(SensorMaster.measure(0),0,1023,0,118));
    // Screen1.draw_sensor_box (140,140,map(SensorMaster.measure(0),0,1023,0,118));
    // Screen1.step_forward();

    // Screen2.draw_graph(map(SensorMaster.measure(2),0,1023,0,118));
    // Screen2.draw_sensor_box (260,140,map(SensorMaster.measure(2),0,1023,0,118));
    // Screen2.step_forward();

    // String dataString = (String)SensorMaster.measure(0);

    // // open the file. note that only one file can be open at a time,
    // // so you have to close this one before opening another.
    // File dataFile = SD.open("datalog.txt", FILE_WRITE);

    // // if the file is available, write to it:
    // if (dataFile) {
    //     dataFile.println(dataString);
    //     dataFile.close();
    //     // print to the serial port too:
    //     Serial.println(dataString);
    // }
    // // if the file isn't open, pop up an error:
    // else {
    //     Serial.println("error opening datalog.txt");
    // }
}