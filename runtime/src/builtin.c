#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct Interval {
  int32_t min;
  int32_t max;
};

/* Length Builtin Function*/

int32_t lengthIntVec(int32_t* vector) {
  int32_t size = ((int32_t*)vector)[0];
  return size;
}

int32_t lengthBoolVec(bool* vector) {
  int32_t size = ((int32_t*)vector)[0];
  return size;
}

int32_t lengthCharVec(int8_t* vector) {
  int32_t size = ((int32_t*)vector)[0];
  return size;
}

int32_t lengthFloatVec(float* vector) {
  int32_t size = ((int32_t*)vector)[0];
  return size;
}

int32_t lengthInterval(struct Interval* interval) {
  return interval->max - interval->min + 1;
}

/* Row + Col Builtin Function*/

int32_t rowIntMatrix(int32_t* matrix) {
  int32_t size = ((int32_t*)matrix)[1];
  return size;
}

bool rowBoolMatrix(bool* matrix) {
  int32_t size = ((int32_t*)matrix)[1];
  return size;
}

int32_t rowCharMatrix(int8_t* matrix) {
  int32_t size = ((int32_t*)matrix)[1];
  return size;
}

int32_t rowFloatMatrix(float* matrix) {
  int32_t size = ((int32_t*)matrix)[1];
  return size;
}

int32_t colIntMatrix(int32_t* matrix) {
  int32_t size = ((int32_t*)matrix)[0];
  return size;
}

bool colBoolMatrix(bool* matrix) {
  int32_t size = ((int32_t*)matrix)[0];
  return size;
}

int32_t colCharMatrix(int8_t* matrix) {
  int32_t size = ((int32_t*)matrix)[0];
  return size;
}

int32_t colFloatMatrix(float* matrix) {
  int32_t size = ((int32_t*)matrix)[0];
  return size;
}

/* Reverse Builtin Function*/
int32_t* reverseIntVec(int32_t* vector) {
  int32_t size = *(int32_t*)vector;
  int32_t* data = (int32_t*)(((int32_t*)vector) + 1);

  for (int i = 0; i < size / 2; i++) {
    int32_t temp = data[i];
    data[i] = data[size-i-1];
    data[size-i-1] = temp;
  }

  return vector;
}

bool* reverseBoolVec(bool* vector) {
  int32_t size = *(int32_t*)vector;
  bool* data = (bool*)(((int32_t*)vector) + 1);

  for (int i = 0; i < size / 2; i++) {
    bool temp = data[i];
    data[i] = data[size-i-1];
    data[size-i-1] = temp;
  }

  return vector;
}

int8_t* reverseCharVec(int8_t* vector) {
  int32_t size = *(int32_t*)vector;
  int8_t* data = (int8_t*)(((int32_t*)vector) + 1);

  for (int i = 0; i < size / 2; i++) {
    int8_t temp = data[i];
    data[i] = data[size-i-1];
    data[size-i-1] = temp;
  }

  return vector;
}

float* reverseRealVec(float* vector) {
  int32_t size = *(int32_t*)vector;
  float* data = (float*)(((int32_t*)vector) + 1);

  for (int i = 0; i < size / 2; i++) {
    float temp = data[i];
    data[i] = data[size-i-1];
    data[size-i-1] = temp;
  }

  return vector;
}

// TODO: work on stream state
int streamState() {
  if (ferror(stdin)) {
    return 1;
  }
  else if (feof(stdin)) {
    return 2;
  }
  else {
    return 0;
  }
}