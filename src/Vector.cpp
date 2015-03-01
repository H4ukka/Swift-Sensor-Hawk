#include <stdlib.h>
#include "vector.h"

/**
*
* A C-style int vector implementation based on Happy Bear Software Tutorial
* http://www.happybearsoftware.com/implementing-a-dynamic-array.html
*
**/

void Vector::init() {
  // initialize size and capacity
  size_ = 0;
  capacity_ = 5;

  // allocate memory for data
  data_ = (int*) malloc(sizeof(int) * capacity_);
}

void Vector::append(int value) {
  // make sure there's room to expand into
  double_capacity_if_full();

  // append the value and increment size
  data_[size_++] = value;
}

int Vector::get(int index) {
  if (index >= size_ || index < 0) {
    // Throw error
  }
  return data_[index];
}

void Vector::set(int index, int value) {
  // zero fill the vector up to the desired index
  while (index >= size_) {
    append(0);
  }

  // set the value at the desired index
  data_[index] = value;
}

void Vector::double_capacity_if_full() {
  if (size_>= capacity_) {
    // double capacity and resize the allocated memory accordingly
    capacity_ *= 2;
    data_ = (int*) realloc(data_, sizeof(int) * capacity_);
  }
}

void Vector::vec_free() {
  free(data_);
}