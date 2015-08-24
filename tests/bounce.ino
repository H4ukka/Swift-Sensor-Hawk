const short s = 400;

unsigned int tdata [s];
short data [s];

void setup()
{
	Serial.begin(9600);
	Serial.println("----- START -----");
	delay(400);
}

void loop()
{
	short j = 0;

	while (j < s) {
		data [j] = ADConvert(B0000);
		tdata [j] = micros();
		j++;
	}

	Serial.println("----- END / DATA START -----");

	for (int i = 0; i < s; i++) {

		Serial.print(data [i]);
		Serial.print(',');
		Serial.print(tdata [i]);
		Serial.print('\n');
	}

	Serial.println("----- DATA END -----");

	while(1){}
}

/*
	Analog to Digital conversion function; you give it a channel code as a nibble
	and it'll spit out a value between (0 -> 1023) representing that channels current
	voltage level

	ATMega328 ADC pins:

	id | nibble
	---|-------
	A0 | B0000
	A1 | B0001
	A2 | B0010
	A3 | B0011
	A4 | B0100
	A5 | B0101
	A6 | B0110
	A7 | B0111
*/

int ADConvert (byte channel) {

	DIDR0 = 0xFF;								// Disable all digital input pins on the ADC
	ADMUX = 0x40 | channel;       				// 0x40 = Analog Comparator Multiplexer Enable (ACME)
												// we OR the channel nibble to select the wanted channel via ADMUX (p. 242 ds.)
	ADCSRA = 0xC7;								// Enable ADC and start the conversion process; set the prescaler factor to 128

	while ( (ADCSRA & 0x40) != 0);				// When the conversion is done the ADC will set the ADSC bit to 0; until then we wait

	return ADC;									// Once we're done return the contents of the ADC register
}