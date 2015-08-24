bool p = false;

void setup()
{

	DDRB = DDRB | B00000000;

	Serial.begin(9600);
	Serial.println("----- START -----");
}

void loop()
{
	short pin = PINB;

	if (pin & B00000010 && !p)
	{
		Serial.println("pressed");
		p = true;
	}

	if (!(pin & B00000010) && p)
	{
		p = false;
	}
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