/*
    NAME:   Swift Sensor Hawk
    DATE:   25.02.2015 (start) / 20.8.2015 (last)
    VER:    v0r2 

    -----------------------
    MIT License
    -----------------------
    author: laine.antti.e@gmail.com

*/

#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "waves.h"
#include "beeps.h"
#include "led.h"

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

short tc = 0;
short gc = 0;
short ac = 0;

bool alert = false;
bool reset = false;
bool below_limit = true;
bool af = false;

void setup () {

    LCD0_.InitLCD();

    Serial.begin(9600);

    SensorMaster.addChannel(0, RED_4);
    SensorMaster.addChannel(2, GREEN_4);
    SensorMaster.addChannel(4, BLUE_4);

    SensorMaster.setLimit(0,28);
    SensorMaster.setLimit(1,60);
    SensorMaster.setLimit(2,65);

    cli();

    TCCR3A = 0;
    TCCR3B = (1 << CS31);								// 8 prescaler
    TIMSK3 = (1 << TOIE3);								// Timer3 Overflow Interrupt

    /**
    * AUDIO - v1
    **/

    TCCR1B  = (1 << CS10);                              // Set prescaler to full 16MHz
    TCCR1A |= (1 << COM1A1);                            // PWM pin to go low when TCNT1=OCR1A
    TCCR1A |= (1 << WGM10);                             // Put timer into 8-bit fast PWM mode
    TCCR1B |= (1 << WGM12);                             // CTC Mode enable

    TCCR2A = 0;                                         // We need no options in control register A
    TCCR2B = (1 << CS21);                               // Set prescaler to divide by 8
    TIMSK2 = (1 << OCIE2A);                             // Set timer to call ISR when TCNT2 = OCRA2

    // Button pins
    DDRK = 0b11111000;

    // LED and AUDIO pins
    DDRB = DDRB | B00110000;

    sei();

    Screen.draw_view ("MAIN_VIEW");

}

void loop () {

    short portk = PINK;

    if ((portk & 0b00000001) && Screen.view() != LEFT) {
        Screen.draw_view ("LEFT_VIEW");
    }
    else if ((portk & 0b00000010) && Screen.view() != CENTER) {
        Screen.draw_view ("MAIN_VIEW");
    }
    else if ((portk & 0b0000100) && Screen.view() != RIGHT) {
        alert_reset();

        if(!below_limit) {
        	led_on(RED);
        }
    }

    if (!below_limit && !af) {
        alert_on();
        af = true;
    }

    if (below_limit && reset) {
        led_off(RED);
        af = false;
        reset = false;
    }

    if(Screen.is_drawn) {

        if (tc == 24 && Screen.view() == CENTER) {

            Screen.draw_sensor_box (58, 130, SensorMaster.getChannel(0));
            Screen.draw_sensor_box (172, 130, SensorMaster.getChannel(1));
            Screen.draw_sensor_box (286, 130, SensorMaster.getChannel(2));

            Screen.draw_stats_box (58, 181, SensorMaster.getChannel(0));
            Screen.draw_stats_box (172, 181, SensorMaster.getChannel(1));
            Screen.draw_stats_box (286, 181, SensorMaster.getChannel(2));
        }

        if(gc == 8 && (Screen.view() == CENTER || Screen.view() == LEFT)) {

            SensorMaster.measure(0);
            SensorMaster.measure(1);
            SensorMaster.measure(2);

            if (!SensorMaster.valuesBelowLimits()) {
                below_limit = false;
            }else{
                below_limit = true;
            }

            Screen.draw_graph(SensorMaster.getChannel(0));
            Screen.draw_graph(SensorMaster.getChannel(1));
            Screen.draw_graph(SensorMaster.getChannel(2));

            Screen.draw_limit(SensorMaster.getChannel(0));
            Screen.draw_limit(SensorMaster.getChannel(1));
            Screen.draw_limit(SensorMaster.getChannel(2));

            Screen.step_forward();
        }
    }
}

void alert_on () {
    sound = true;
    alert = true;
    OCR2A = 20;
}

void alert_reset () {

    sound = false;
    alert = false;
    reset = true;
}

ISR(TIMER3_OVF_vect) {

    if(Screen.is_drawn) {

        if (tc == 24 && Screen.view() == CENTER) {
            tc = 0;

        }else if (Screen.view() == CENTER){
            tc++;
        }

        if(gc == 8 && (Screen.view() == CENTER || Screen.view() == LEFT)) {
            gc = 0;
        }else if (Screen.view() == CENTER || Screen.view() == LEFT){
            gc++;
        }

        if (alert && ac > 1) {
            sound = !sound;
            ac = 0;
            led_toggle(RED);
        }else{
            ac++;
        }
    }
}

ISR(TIMER2_COMPA_vect) {

    static byte index = 0;
    
    if (sound) {
        OCR1AL = pgm_read_byte(&WAVES[1][index++]);
        asm("NOP;NOP");
        TCNT2 = 6;
    }
}   