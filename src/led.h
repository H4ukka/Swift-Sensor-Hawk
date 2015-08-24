#define RED 						0		// LED pin defenitions
#define GREEN 						1

#define RED_LED_PORT_PIN			0x10	// Output port pins for LEDs
#define GREEN_LED_PROT_PIN			0x80

void led_on (byte pin) {

	switch (pin) {
		case RED: 		PORTB = (1<<PD4); break;
		case GREEN: 	;
	}
}

void led_off (byte pin) {

	switch (pin) {
		case RED: 		PORTB = (0<<PD4); break;
		case GREEN: 	;
	}
}

void led_toggle (byte pin) {
	switch (pin) {
		case RED: 		PORTB = PORTB ^ RED_LED_PORT_PIN; break;
		case GREEN: 	;
	}
}