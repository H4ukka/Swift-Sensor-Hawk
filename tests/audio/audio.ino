#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "music.h"
#include "waves.h"
#include "beeps.h"

short x = 0;

void setup()
{

	DDRD = DDRD | B10000000;
	DDRB = DDRB | B00000011;

	cli();												// Disable interrupts

	TCCR1B  = (1 << CS10);          					// Set prescaler to full 16MHz
	TCCR1A |= (1 << COM1A1);        					// PWM pin to go low when TCNT1=OCR1A
	TCCR1A |= (1 << WGM10);         					// Put timer into 8-bit fast PWM mode
	TCCR1B |= (1 << WGM12);								// CTC Mode enable


	TCCR2A = 0;                     					// We need no options in control register A
	TCCR2B = (1 << CS21);           					// Set prescaler to divide by 8
	TIMSK2 = (1 << OCIE2A);         					// Set timer to call ISR when TCNT2 = OCRA2

	sei();

	play_song (2, LOOP);
}

void loop()
{
	// if(x == 4600) {
	// 	if (c_ <= 0) {
	// 		if (!pause) {
	// 			sound = true;
	// 			OCR2A = pgm_read_word_near(note_ptr + PITCH_OFFSET);
	// 			c_ = pgm_read_word_near(note_ptr);

	// 			if (pgm_read_word_near(note_ptr + PAUSE_OFFSET) != 0) {
	// 				pause = true;
	// 			}else{
	// 				pause = false;
	// 				note_ptr += NOTE_STEPPING;
	// 			}
	// 		}else{
	// 			sound = false;
	// 			c_ = pgm_read_word_near(note_ptr + PAUSE_OFFSET);
	// 			pause = false;
	// 			note_ptr += NOTE_STEPPING;
	// 		}
	// 	}	
	// 	if (note_ptr - start_ptr > song_length) {
	// 		if (loop_enabled) {
	// 			note_ptr = start_ptr;
	// 			c_ = 0;
	// 		}else{
	// 			sound = false;
	// 			music_enabled = false;
	// 		}
	// 	}else{
	// 		c_--;
	// 	}
	// 	x = 0;
	// }else{
	// 	x++;
	// }

	// Alarm Sound
	n_ (100, 10, 100);
	n_ (100, 10, 100);
	n_ (100, 10, 100);
	n_ (100, 10, 100);
	n_ (100, 10, 100);

}

/*
	This Interrupt Service Routine is used to load the next sample from the currently used wavetable
	We have some magical assembly calls to compensate the time the processor takes to jump (hoops!)
	"NOP;NOP" just means "do nothing for 2 cycles"

	TCNT2 has to be adjusted at the end; otherwise we're going to sound terrible
	'6' seems to be the right magical number for compensating the time we spent in the ISR call

	The index variable stores the index value of the current sample in the wavetable
	During each ISR call we increment it by 1 to laod the next sample
	When the index value reaches 255 it will overflow back to 0 since it's defined as a byte
*/

ISR(TIMER2_COMPA_vect) {

	static byte index = 0;
	
	if (sound) {
		OCR1AL = pgm_read_byte(&WAVES[0][index++]);
		asm("NOP;NOP");
		TCNT2 = 6;
	}
}