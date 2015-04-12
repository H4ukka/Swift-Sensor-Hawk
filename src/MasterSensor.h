#ifndef MASTER_SENSOR_H
#define MASTER_SENSOR_H

#define MAX_CHANNELS 5

/* Typedef for function pointers */
typedef int (*function_pointer)(short);

class MasterSensor {
public:
    MasterSensor (function_pointer);
    ~MasterSensor ();

    /* Methods */
    int measure (short);
    void scan ();
    void addChannel (short);

    short getChannelId (short);

private:
    function_pointer adcp_;
    short sensor_channels_[MAX_CHANNELS];
};

#endif