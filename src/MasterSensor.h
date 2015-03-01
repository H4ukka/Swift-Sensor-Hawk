#ifndef MASTER_SENSOR_H
#define MASTER_SENSOR_H

#include "vector.h"

/* Typedef for function pointers */

typedef int (*function_pointer)(short);

class MasterSensor {
public:
    MasterSensor (function_pointer);
    ~MasterSensor ();

    /* Methods */
    int measure ();
    void scan ();

private:
    function_pointer adcp_;
    Vector sensor_ports_;
};

#endif