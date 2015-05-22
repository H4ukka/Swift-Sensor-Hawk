#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "music.h"
#include "waves.h"
#include "beeps.h"

long cc = 0;

void setup() {

	DDRD = DDRD | B10000000;            				// D7 to output mode
	DDRB = DDRB | B00000011;							// D8 and D9 to output mode
	/* --------- */
	cli();												// Disable interrupts

	TCCR1B  = (1 << CS10);          					// Set prescaler to full 16MHz
	TCCR1A |= (1 << COM1A1);        					// PWM pin to go low when TCNT1=OCR1A
	TCCR1A |= (1 << WGM10);         					// Put timer into 8-bit fast PWM mode
	TCCR1B |= (1 << WGM12);								// CTC Mode enable


	TCCR2A = 0;                     					// We need no options in control register A
	TCCR2B = (1 << CS21);           					// Set prescaler to divide by 8
	TIMSK2 = (1 << OCIE2A);         					// Set timer to call ISR when TCNT2 = OCRA2

	sei();                          					// Enable interrupts
	/* --------- */

	play_song(CANON, LOOP);
}

void loop() {

	if (cc == 160000) {

		if (music_enabled) {

			if (c_ <= 0) {
				if (!pause) {
					sound = true;
					OCR2A = pgm_read_word_near(note_ptr + PITCH_OFFSET);
					c_ = pgm_read_word_near(note_ptr);

					if (pgm_read_word_near(note_ptr + PAUSE_OFFSET) != 0) {
						pause = true;
					}else{
						pause = false;
						note_ptr += NOTE_STEPPING;
					}
				}else{
					sound = false;
					c_ = pgm_read_word_near(note_ptr + PAUSE_OFFSET);
					pause = false;
					note_ptr += NOTE_STEPPING;
				}
			}	
			if (note_ptr - start_ptr > song_length) {
				if (loop_enabled) {
					note_ptr = start_ptr;
					c_ = 0;
				}else{
					sound = false;
					music_enabled = false;
				}
			}else{
				c_--;
			}
		}
		cc = 0;
	}else{
		cc++;
	}
}

ISR(TIMER2_COMPA_vect) {

	static byte index = 0;
	
	if (sound) {
		OCR1AL = pgm_read_byte(&WAVES[6][index++]);
		asm("NOP;NOP");
		TCNT2 = 6;
	}
}