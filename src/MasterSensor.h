#ifndef MASTER_SENSOR_H
#define MASTER_SENSOR_H

typedef int (*FP)(short);

class MasterSensor {
public:
	MasterSensor (FP);

	/* Methods */
    int measure ();

private:
	FP _adcp;
};

#endif