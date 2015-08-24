SdFat sd;
SdFile stream;

const int chipSelect = 53;

bool card_enabled;

#define CHANNEL_COUNT 0
#define CHANNEL_1_MOD 1
#define CHANNEL_2_MOD 2
#define CHANNEL_3_MOD 3

#define CONFIG_LINES 4

int config_values [CONFIG_LINES];

void init_card () {

    // see if the card is present and can be initialized:
    if (!sd.begin(chipSelect, SPI_HALF_SPEED)) {
        // don't do anything more:
        card_enabled = false;
        sd.initErrorHalt();
        return;
    }else{
        card_enabled = true;
    }
}

void save_default_config () {
    
    if (card_enabled) {
        stream.open("config.cnf", O_RDWR | O_CREAT | O_AT_END);
        stream.println ("1#number of active channels.");
        stream.println ("1.318392#channel 1 multiplier.");
        stream.println ("0#channel 2 multiplier.");
        stream.println ("0#channel 3 multiplier.");
        stream.println ("#end of config");
        stream.close();
    }
}

void parse_config () {

	if (card_enabled) {

		if (!stream.open("config.cnf", O_READ)) {
		}

		char data;
		String line;

		for (int i = 0; i < CONFIG_LINES; i++) {

			line = "";
			data = ' ';

			while((data = stream.read()) != '#') {
				line += data;
			}

			config_values[i] = line.toFloat();
		}
		stream.close();
	}
}

float get_config_value (int index) {
	return config_values[index];
}
