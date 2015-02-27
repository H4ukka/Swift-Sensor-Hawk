#ifndef MASTER_SENSOR_H
#define MASTER_SENSOR_H

/* Typedef for function pointers */

typedef int (*function_pointer)(short);

class MasterSensor {
public:
    MasterSensor (function_pointer);

    /* Methods */
    int measure ();

private:
    function_pointer adcp_;
};

#endif