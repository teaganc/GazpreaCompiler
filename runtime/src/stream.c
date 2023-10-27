#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

struct Interval {
  int32_t min;
  int32_t max;
};

void printNull() {
  printf("%c", 0);
}

void printIdentity() { printf("%c", 1); }

void printInt(int32_t value) { printf("%d", value); }

void printFloat(float value) { printf("%g", value); }

void printChar(char value) { printf("%c", value); }

void printBool(bool value) {
  if (value) {
    printf("T");
  } else {
    printf("F");
  }
}
// Intervals are upcasted to int vectors
void printIntVecHelper(int32_t* data, int32_t size) {
  printf("[");
  if (size) {
    printf("%i", *data);
  }
  for(int i = 1; i < size; i++) {
    printf(" %i" , data[i]);
  }
  printf("]");
}
 
void printFloatVecHelper(float* data, int32_t size) {
  printf("[");
  if (size) {
    printf("%g", *data);
  }
  for(int i = 1; i < size; i++) {
    printf(" %g" , data[i]);
  }
  printf("]");
}
 
void printCharVecHelper(int8_t* data, int32_t size) {
  printf("[");
  if (size) {
    printf("%c", *data);
  }
  for(int i = 1; i < size; i++) {
    printf(" %c" , data[i]);
  }
  printf("]");
}
 
void printBoolVecHelper(bool* data, int32_t size) {
  printf("[");
  if (size) {
    printBool(*data);
  }
  for(int i = 1; i < size; i++) {
    printf(" ");
    printBool(data[i]);
  }
  printf("]");
}

void printInterval(struct Interval* interval) {
  printf("[");
  printf("%i", interval->min);
  for(int i = interval->min + 1; i <= interval->max; i++) {
    printf(" %i" , i);
  }
  printf("]");
  free(interval);
}

void printIntVec(int32_t* vector) {
  int32_t size = *(int32_t*)vector;
  int32_t* data = (int32_t*)(((int32_t*)vector) + 1);
  printIntVecHelper(data, size);
}
void printFloatVec(float* vector) {
  int32_t size = *(int32_t*)vector;
  float* data = (float*)(((int32_t*)vector) + 1);
  printFloatVecHelper(data, size);
  fflush(stdin);
}

void printCharVec(int8_t* vector) {
  int32_t size = *(int32_t*)vector;
  int8_t* data = (int8_t*)(((int32_t*)vector) + 1);
  printCharVecHelper(data, size);
}
void printBoolVec(bool* vector) {
  int32_t size = *(int32_t*)vector;
  bool* data = (bool*)(((int32_t*)vector) + 1);
  printBoolVecHelper(data, size);
}
 
void printString(int8_t* vector) {
  int32_t size = *(int32_t*)vector;
  int8_t* data = (int8_t*)(((int32_t*)vector) + 1);
  for (int i = 0; i < size; i++) {
    printf("%c", data[i]);
  }
}
 
void printIntMat(int32_t* matrix) {
  int32_t size0 = *(int32_t*)matrix;
  int32_t size1 = *(((int32_t*)matrix) + 1);
  int32_t* data = (int32_t*)(((int32_t*)matrix) + 2);
  printf("[");
  if (size0) {
    printIntVecHelper(data, size1);
  }
  for (int i = 1; i < size0; i++) {
    printf(" ");
    printIntVecHelper(data + i * size1, size1);
  }
  printf("]");
}

void printFloatMat(float* matrix) {
  int32_t size0 = *(int32_t*)matrix;
  int32_t size1 = *(((int32_t*)matrix) + 1);
  float* data = (float*)(((int32_t*)matrix) + 2);
  printf("[");
  if (size0) {
    printFloatVecHelper(data, size1);
  }
  for (int i = 1; i < size0; i++) {
    printf(" ");
    printFloatVecHelper(data + i * size1, size1);
  }
  printf("]");
}
void printCharMat(int8_t* matrix) {
  int32_t size0 = *(int32_t*)matrix;
  int32_t size1 = *(((int32_t*)matrix) + 1);
  int8_t* data = (int8_t*)(((int32_t*)matrix) + 2);
  printf("[");
  if (size0) {
    printCharVecHelper(data, size1);
  }
  for (int i = 1; i < size0; i++) {
    printf(" ");
    printCharVecHelper(data + i * size1, size1);
  }
  printf("]");
}
void printBoolMat(bool* matrix) {
  int32_t size0 = *(int32_t*)matrix;
  int32_t size1 = *(((int32_t*)matrix) + 1);
  bool* data = (bool*)(((int32_t*)matrix) + 2);
  printf("[");
  if (size0) {
    printBoolVecHelper(data, size1);
  }
  for (int i = 1; i < size0; i++) {
    printf(" ");
    printBoolVecHelper(data + i * size1, size1);
  }
  printf("]");
}

int32_t inputInt() {
  int32_t value;
  if (scanf("%d", &value) <= 0) {
    inputIntError();
  }
  return value;
}

float inputFloat() {
  float value;
  if (scanf("%f", &value) <= 0) {
    inputFloatError();
  }
  checkNan(value);
  return value;
}
char inputChar() {
  char value;
  if (scanf("%c", &value) <= 0) {
    inputCharError();
  }
  return value;
}

bool inputBool() {
  char value;
  if (scanf("%c", &value) <= 0) {
    inputBoolError();
  }
  if (value == 'T') {
    return true;
  }
  else if (value == 'F') {
    return false;
  }
  else {
    inputBoolError();
  }
}