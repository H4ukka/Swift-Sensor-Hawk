#ifndef MASTER_SENSOR_H
#define MASTER_SENSOR_H

#define MAX_CHANNELS 5

#include "Channel.h"

/* Typedef for function pointers */
typedef int (*function_pointer)(short);

class MasterSensor {
public:
    MasterSensor (function_pointer);
    ~MasterSensor ();

    /* Methods */
    bool measure (short);
    void scan ();
    void addChannel (short, short, short, short);
    void setChannelColor (short, short, short, short);
    void setLimit (short, short);
    void setMultiplier (short, float);

    short getChannelId (short);

    Channel * getChannel (short);

private:

    float convertd (short);

    function_pointer adcp_;

    short next_free_channel_;

    Channel channels_ [MAX_CHANNELS];
};

#endif