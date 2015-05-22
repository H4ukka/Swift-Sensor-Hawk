#ifndef CHANNEL_H
#define CHANNEL_H

struct Channel {

    short id;

    double total;

    int count;

    short R;
    short G;
    short B;

    short prev_X;
    short prev_Y;

    short value;
    short min;
    short max;
};

#endif