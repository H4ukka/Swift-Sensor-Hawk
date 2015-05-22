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
#include "MasterButton.h"
#include "hardware.h"

UTFT LCD0_(CTE32W,38,39,40,41);


MasterSensor SensorMaster (g_get_adc);
MasterButton ButtonMaster;
ScreenDrawer Screen;

const int chipSelect = 53;

short tc = 0;
short gc = 0;

void setup () {

    Serial.begin(9600);

    LCD0_.InitLCD();

    SensorMaster.addChannel(3, DEFAULT_RED);
    // SensorMaster.addChannel(4, DEFAULT_GREEN);
    // SensorMaster.addChannel(5, DEFAULT_YELLOW);

    Screen.draw_view ("MAIN_VIEW");

    //Serial.print("Initializing SD card...");

    // // see if the card is present and can be initialized:
    // if (!SD.begin(chipSelect)) {
    //     Serial.println("Card failed, or not present");
    //     // don't do anything more:
    //     return;
    // }
    // Serial.println("card initialized.");

    cli();

    TCCR3A = 0;
    TCCR3B = (1 << CS31);
    TIMSK3 = (1 << TOIE3);

    // DDRK = 0b00000000;

    sei();

}

void loop () {

	// short portk = PINK;

	// if (portk & 0b0000001 && Screen.view() != LEFT) {
	// 	Screen.draw_view ("LEFT_VIEW");
	// }
	// else if (portk & 0b0000010 && Screen.view() != CENTER) {
	// 	Screen.draw_view ("MAIN_VIEW");
	// }
	// else if (portk & 0b0000100 && Screen.view() != RIGHT) {
	// 	Screen.draw_view ("RIGHT_VIEW");
	// }


    // Screen.draw_graph( 120-(SensorMaster.measure(0)-380), SensorMaster.getChannel(0));
    // Screen.draw_sensor_box (20,140,(502 - SensorMaster.measure(0))*1.494, SensorMaster.getChannel(0));

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

ISR(TIMER3_OVF_vect) {

    SensorMaster.measure(0);
    // SensorMaster.measure(1);
    // SensorMaster.measure(2);

    if(Screen.is_drawn_ && Screen.view() == CENTER) {

	    if(gc == 8) {

	        Screen.draw_graph(SensorMaster.getChannel(0));
	        // Screen.draw_graph(SensorMaster.getChannel(1));
	        // Screen.draw_graph(SensorMaster.getChannel(2));

	        Screen.step_forward();

	        gc = 0;
	    }else{

	        gc++;
	    }

	    if (tc == 25) {

	        Screen.draw_sensor_box (0, 125, SensorMaster.getChannel(0));
	        // Screen.draw_sensor_box (100, 125, SensorMaster.getChannel(1));
	        // Screen.draw_sensor_box (200, 125, SensorMaster.getChannel(2));

	        Screen.draw_stats_box (0, 176, SensorMaster.getChannel(0));
	        // Screen.draw_stats_box (100, 176, SensorMaster.getChannel(1));
	        // Screen.draw_stats_box (200, 176, SensorMaster.getChannel(2));

	        tc = 0;
	    }else{

	        tc++;
	    }
	}
}
    