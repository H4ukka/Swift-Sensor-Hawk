#ifndef MASTER_SENSOR_H
#define MASTER_SENSOR_H

typedef int (*FP)(short);

struct MasterSensor {
    MasterSensor (FP);

    int measure ();

private:
	FP _adcp;
};

#endif