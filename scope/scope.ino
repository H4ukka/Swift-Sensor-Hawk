/*
    NAME:   Swift Sensor Hawk
    DATE:   25.02.2015 (start)
    VER:    v0r1

    DESC:

        Description goes here.
    

    -----------------------
    Copyright stuff here
    -----------------------
    laine.antti.e@gmail.com

    TODO:
    - 
*/

#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include <SPI.h>
#include <SdFat.h>
#include <UTFT.h>

#include "colors.h"
#include "ScreenDrawer.h"
#include "MasterSensor.h"
#include "hardware.h"

UTFT LCD0_(CTE32W,38,39,40,41);

MasterSensor SensorMaster (g_get_adc);
ScreenDrawer Screen;

void setup () {

    Serial.begin(9600);

    LCD0_.InitLCD();

    SensorMaster.addChannel(3, DEFAULT_RED);
    SensorMaster.setLimit(0,300);
    Screen.draw_view ("LEFT_VIEW");

    cli();

    TCCR3A = 0;
    TCCR3B = (1 << CS30);
    TIMSK3 = (1 << TOIE3);

    sei();

}

void loop () {

}

ISR(TIMER3_OVF_vect) {

	SensorMaster.measure(0);
	Screen.draw_graph(SensorMaster.getChannel(0));
	Screen.step_forward();

}   