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
    void measure (short);
    void scan ();
    void addChannel (short, short, short, short);
    void setChannelColor (short, short, short, short);
    void setLimit (short, short);
    void setMultiplier (short, float);

    bool valuesBelowLimits ();

    short getChannelId (short);

    Channel * getChannel (short);

private:
    function_pointer adcp_;

    short next_free_channel_;

    Channel channels_ [MAX_CHANNELS];
};

#endif