#ifndef VECTOR_H
#define VECTOR_H

class Vector {
public:
    void init ();
    void append (int value);
    int  get (int index);
    void set (int index, int value);
    void double_capacity_if_full ();
    void vec_free ();

private:
    int size_;
    int capacity_;
    int *data_;
};

#endif