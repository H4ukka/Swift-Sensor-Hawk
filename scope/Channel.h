#ifndef CHANNEL_H
#define CHANNEL_H

struct Channel {

    short id;

    double total;
    float multiplier;
    short offset;

    int count;

    short R;
    short G;
    short B;

    short prev_X;
    short prev_Y;

    short limit;
    short value;
    short min;
    short max;
};

#endif