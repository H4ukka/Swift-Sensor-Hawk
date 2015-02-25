/*
    This header contains hardware functions. They
    are stored here because they might not work
    if stored inside a struct or a class due to
    code scope
*/

/*
    Analog to Digital conversion function; you give it a channel code as a nibble
    and it'll spit out a value between (0 -> 1023) representing that channels current
    voltage level

    ATMega328 ADC pins:

    id | nibble | short
    ---|--------|-------
    A0 | B0000  | 0
    A1 | B0001  | 1
    A2 | B0010  | 2
    A3 | B0011  | 3
    A4 | B0100  | 4
    A5 | B0101  | 5
    A6 | B0110  | 6
    A7 | B0111  | 7
*/

typedef int (*FP)(short);
    
int get_adc (short channel) {

    DIDR0 = 0xFF;                               // Disable all digital input pins on the ADC
    ADMUX = 0x40 | channel;                     // 0x40 = Analog Comparator Multiplexer Enable (ACME)
                                                // we OR the channel nibble to select the wanted channel via ADMUX (p. 242)
    ADCSRA = 0xC7;                              // Enable ADC and start the conversion process; set the prescaler factor to 128

    while ( (ADCSRA & 0x40) != 0);              // When the conversion is done the ADC will set the ADSC bit to 0; until then we wait

    return ADC;                                 // Once we're done return the contents of the ADC register
}

FP _get_adc = get_adc;