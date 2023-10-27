#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "errors.h"

struct Interval {
  int32_t min;
  int32_t max;
};
/* Scalar Unary operations*/

bool unaryNotBool(bool value) { return !value; }

int32_t unaryPlusInt(int32_t value) { return value; }

float unaryPlusFloat(float value) { return value; }

int32_t unaryMinusInt(int32_t value) { return -value; }

float unaryMinusFloat(float value) { return -value; }

/* Vector Unary operations*/

bool* unaryNotBoolVec(bool* vector) { 
  int32_t size = *((int32_t*)vector);
  bool* data = (bool*)(((int32_t*)vector) + 1);
  for (int i = 0; i < size; i++) {
    data[i] = !(data[i]);
  }
  return vector;
}

int32_t* unaryPlusIntVec(int32_t* vector) { return vector; }

float* unaryPlusFloatVec(float* vector) { return vector; }

int32_t* unaryMinusIntVec(int32_t* vector) { 
  int32_t size = *((int32_t*)vector);
  int32_t* data = (int32_t*)(((int32_t*)vector) + 1);
  for (int i = 0; i < size; i++) {
    data[i] = !(data[i]);
  }
  return vector;
}

float* unaryMinusFloatVec(float* vector) { 
  int32_t size = *((int32_t*)vector);
  float* data = (float*)(((int32_t*)vector) + 1);
  for (int i = 0; i < size; i++) {
    data[i] = !(data[i]);
  }
  return vector;
}

/* Matrix Unary operations*/

bool* unaryNotBoolMat(bool* matrix) {  
  int32_t size0 = *((int32_t*)matrix);
  int32_t size1 = *(((int32_t*)matrix) + 1);
  bool* data = (bool*)(((int32_t*)matrix) + 2);
  for (int i = 0; i < size0; i++) {
    for (int j = 0; j < size1; j++) { 
      data[i * size1 + j] = !(data[i * size1 + j]);
    }
  }
  return matrix;
}
int32_t* unaryPlusIntMat(int32_t* matrix) {
  return matrix;
}
float* unaryPlusFloatMat(float* matrix) {
  return matrix;
}
int32_t* unaryMinusIntMat(int32_t* matrix) {
  int32_t size0 = *((int32_t*)matrix);
  int32_t size1 = *(((int32_t*)matrix) + 1);
  int32_t* data = (int32_t*)(((int32_t*)matrix) + 2);
  for (int i = 0; i < size0; i++) {
    for (int j = 0; j < size1; j++) { 
      data[i * size1 + j] = !(data[i * size1 + j]);
    }
  }
  return matrix;
}
float* unaryMinusFloatMat(float* matrix) {
  int32_t size0 = *((int32_t*)matrix);
  int32_t size1 = *(((int32_t*)matrix) + 1);
  float* data = (float*)(((int32_t*)matrix) + 2);
  for (int i = 0; i < size0; i++) {
    for (int j = 0; j < size1; j++) { 
      data[i * size1 + j] = !(data[i * size1 + j]);
    }
  }
  return matrix;
}

/* Interval Unary operations*/

struct Interval* unaryPlusInterval(struct Interval* interval) {}
struct Interval* unaryMinusInterval(struct Interval* interval) {}

/* Scalar Binary Operations*/

int32_t binaryAddInt(int32_t value1, int32_t value2) { return value1 + value2; }

float binaryAddFloat(float value1, float value2) {
  float ret = value1 + value2;
  checkNan(ret);
  return ret;
}

int32_t binarySubInt(int32_t value1, int32_t value2) { return value1 - value2; }

float binarySubFloat(float value1, float value2) { 
  float ret = value1 - value2;
  checkNan(ret);
  return ret;
}

int32_t binaryMulInt(int32_t value1, int32_t value2) { return value1 * value2; }

float binaryMulFloat(float value1, float value2) { return value1 * value2; }

int32_t binaryDivInt(int32_t value1, int32_t value2) { return value1 / value2; }

float binaryDivFloat(float value1, float value2) { 
  float ret = value1 / value2;
  checkNan(ret);
  return ret;
}

int32_t binaryModInt(int32_t value1, int32_t value2) { return value1 % value2; }

float binaryModFloat(float value1, float value2) {
  float ret = (float)fmod((double)value1, (double)value2);
  checkNan(ret);
  return ret;
}

int32_t binaryExpInt(int32_t value1, int32_t value2) {
  return (int)pow((double)value1, (double)value2);
}

float binaryExpFloat(float value1, float value2) {
  float ret = (float)pow((double)value1, (double)value2);
  checkNan(ret);
  return ret;
}

bool binaryLTInt(int32_t value1, int32_t value2) { return value1 < value2; }

bool binaryLTFloat(float value1, float value2) { return value1 < value2; }

bool binaryLEInt(int32_t value1, int32_t value2) { return value1 <= value2; }

bool binaryLEFloat(float value1, float value2) { return value1 <= value2; }

bool binaryGTInt(int32_t value1, int32_t value2) { return value1 > value2; }

bool binaryGTFloat(float value1, float value2) { return value1 > value2; }

bool binaryGEInt(int32_t value1, int32_t value2) { return value1 >= value2; }

bool binaryGEFloat(float value1, float value2) { return value1 >= value2; }

bool binaryEQInt(int32_t value1, int32_t value2) { return value1 == value2; }

bool binaryEQFloat(float value1, float value2) { return value1 == value2; }

bool binaryEQBool(bool value1, bool value2) { return value1 == value2; }

bool binaryNEInt(int32_t value1, int32_t value2) { return value1 != value2; }

bool binaryNEFloat(float value1, float value2) { return value1 != value2; }

bool binaryNEBool(bool value1, bool value2) { return value1 != value2; }

bool binaryAndBool(bool value1, bool value2) { return value1 & value2; }

bool binaryOrBool(bool value1, bool value2) { return value1 | value2; }

bool binaryXorBool(bool value1, bool value2) { return value1 ^ value2; }

/* Vector Binary Operations*/

int32_t* binaryAddIntVec(int32_t* value1, int32_t* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  int32_t* vec1_data = (int32_t*)(((int32_t*)value1) + 1);
  int32_t* vec2_data = (int32_t*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    vec1_data[i] = binaryAddInt(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return value1;
}

float* binaryAddFloatVec(float* value1, float* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  float* vec1_data = (float*)(((int32_t*)value1) + 1);
  float* vec2_data = (float*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    vec1_data[i] = binaryAddFloat(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return value1;
}

int32_t* binarySubIntVec(int32_t* value1, int32_t* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  int32_t* vec1_data = (int32_t*)(((int32_t*)value1) + 1);
  int32_t* vec2_data = (int32_t*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    vec1_data[i] =  binarySubInt(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return value1;
}

float* binarySubFloatVec(float* value1, float* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  float* vec1_data = (float*)(((int32_t*)value1) + 1);
  float* vec2_data = (float*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    vec1_data[i] =  binarySubFloat(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return value1;
}

int32_t* binaryMulIntVec(int32_t* value1, int32_t* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  int32_t* vec1_data = (int32_t*)(((int32_t*)value1) + 1);
  int32_t* vec2_data = (int32_t*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    vec1_data[i] = binaryMulInt(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return value1;
}

float* binaryMulFloatVec(float* value1, float* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  float* vec1_data = (float*)(((int32_t*)value1) + 1);
  float* vec2_data = (float*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    vec1_data[i] = binaryMulFloat(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return value1;
}

int32_t* binaryDivIntVec(int32_t* value1, int32_t* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  int32_t* vec1_data = (int32_t*)(((int32_t*)value1) + 1);
  int32_t* vec2_data = (int32_t*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    vec1_data[i] = binaryDivInt(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return value1;
}

float* binaryDivFloatVec(float* value1, float* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  float* vec1_data = (float*)(((int32_t*)value1) + 1);
  float* vec2_data = (float*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    vec1_data[i] = binaryDivFloat(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return value1;
}

int32_t* binaryModIntVec(int32_t* value1, int32_t* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  int32_t* vec1_data = (int32_t*)(((int32_t*)value1) + 1);
  int32_t* vec2_data = (int32_t*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    vec1_data[i] = binaryModInt(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return value1;
}

float* binaryModFloatVec(float* value1, float* value2) {
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  float* vec1_data = (float*)(((int32_t*)value1) + 1);
  float* vec2_data = (float*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    vec1_data[i] = binaryModFloat(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return value1;
}

int32_t* binaryExpIntVec(int32_t* value1, int32_t* value2) {
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  int32_t* vec1_data = (int32_t*)(((int32_t*)value1) + 1);
  int32_t* vec2_data = (int32_t*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    vec1_data[i] = binaryExpFloat(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return value1;
}

float* binaryExpFloatVec(float* value1, float* value2) {
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  float* vec1_data = (float*)(((int32_t*)value1) + 1);
  float* vec2_data = (float*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    vec1_data[i] = binaryExpFloat(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return value1;
}

bool* binaryLTIntVec(int32_t* value1, int32_t* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  int32_t* vec1_data = (int32_t*)(((int32_t*)value1) + 1);
  int32_t* vec2_data = (int32_t*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    ((bool*)vec1_data)[i] = binaryLTInt(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return (bool*)value1;
}

bool* binaryLTFloatVec(float* value1, float* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  float* vec1_data = (float*)(((int32_t*)value1) + 1);
  float* vec2_data = (float*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    ((bool*)vec1_data)[i] = binaryLTFloat(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return (bool*)value1;
}

bool* binaryLEIntVec(int32_t* value1, int32_t* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  int32_t* vec1_data = (int32_t*)(((int32_t*)value1) + 1);
  int32_t* vec2_data = (int32_t*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    ((bool*)vec1_data)[i] = binaryLEInt(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return (bool*)value1;
}

bool* binaryLEFloatVec(float* value1, float* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  float* vec1_data = (float*)(((int32_t*)value1) + 1);
  float* vec2_data = (float*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    ((bool*)vec1_data)[i] = binaryLEFloat(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return (bool*)value1;
}

bool* binaryGTIntVec(int32_t* value1, int32_t* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  int32_t* vec1_data = (int32_t*)(((int32_t*)value1) + 1);
  int32_t* vec2_data = (int32_t*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    ((bool*)vec1_data)[i] = binaryGTInt(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return (bool*)value1;
}

bool* binaryGTFloatVec(float* value1, float* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  float* vec1_data = (float*)(((int32_t*)value1) + 1);
  float* vec2_data = (float*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    ((bool*)vec1_data)[i] = binaryGTFloat(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return (bool*)value1;
}

bool* binaryGEIntVec(int32_t* value1, int32_t* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  int32_t* vec1_data = (int32_t*)(((int32_t*)value1) + 1);
  int32_t* vec2_data = (int32_t*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    ((bool*)vec1_data)[i] = binaryGEInt(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return (bool*)value1;
}

bool* binaryGEFloatVec(float* value1, float* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  float* vec1_data = (float*)(((int32_t*)value1) + 1);
  float* vec2_data = (float*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    ((bool*)vec1_data)[i] = binaryGEFloat(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return (bool*)value1;
}

bool binaryEQIntVec(int32_t* value1, int32_t* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  int32_t* vec1_data = (int32_t*)(((int32_t*)value1) + 1);
  int32_t* vec2_data = (int32_t*)(((int32_t*)value2) + 1);
  bool ret = true;
  for (int i = 0; i < vec1_size; i++) {
    ret &= binaryEQInt(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return ret;
}

bool binaryEQFloatVec(float* value1, float* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  float* vec1_data = (float*)(((int32_t*)value1) + 1);
  float* vec2_data = (float*)(((int32_t*)value2) + 1);
  bool ret = true;
  for (int i = 0; i < vec1_size; i++) {
    ret &= binaryEQFloat(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return ret;
}

bool binaryEQBoolVec(bool* value1, bool* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  bool* vec1_data = (bool*)(((int32_t*)value1) + 1);
  bool* vec2_data = (bool*)(((int32_t*)value2) + 1);
  bool ret = true;
  for (int i = 0; i < vec1_size; i++) {
    ret &= binaryEQBool(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return ret;
}

bool binaryNEIntVec(int32_t* value1, int32_t* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  int32_t* vec1_data = (int32_t*)(((int32_t*)value1) + 1);
  int32_t* vec2_data = (int32_t*)(((int32_t*)value2) + 1);
  bool ret = false;
  for (int i = 0; i < vec1_size; i++) {
    ret |= binaryNEInt(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return ret;
}

bool binaryNEFloatVec(float* value1, float* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  float* vec1_data = (float*)(((int32_t*)value1) + 1);
  float* vec2_data = (float*)(((int32_t*)value2) + 1);
  bool ret = false;
  for (int i = 0; i < vec1_size; i++) {
    ret |= binaryNEFloat(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return ret;
}

bool binaryNEBoolVec(bool* value1, bool* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  bool* vec1_data = (bool*)(((int32_t*)value1) + 1);
  bool* vec2_data = (bool*)(((int32_t*)value2) + 1);
  bool ret = false;
  for (int i = 0; i < vec1_size; i++) {
    ret |= binaryNEBool(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return ret;
}

bool* binaryAndBoolVec(bool* value1, bool* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  bool* vec1_data = (bool*)(((int32_t*)value1) + 1);
  bool* vec2_data = (bool*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    vec1_data[i] = binaryAndBool(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return value1;
}

bool* binaryOrBoolVec(bool* value1, bool* value2) { 
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  bool* vec1_data = (bool*)(((int32_t*)value1) + 1);
  bool* vec2_data = (bool*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    vec1_data[i] = binaryOrBool(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return value1;
}

bool* binaryXorBoolVec(bool* value1, bool* value2) {
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  bool* vec1_data = (bool*)(((int32_t*)value1) + 1);
  bool* vec2_data = (bool*)(((int32_t*)value2) + 1);
  for (int i = 0; i < vec1_size; i++) {
    vec1_data[i] = binaryXorBool(vec1_data[i], vec2_data[i]);
  }
  free(value2);
  return value1;
}

/* Matrix Binary Operations*/

int32_t* binaryAddIntMat(int32_t* value1, int32_t* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  int32_t* mat1_data = (int32_t*)(((int32_t*)value1) + 2);
  int32_t* mat2_data = (int32_t*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      mat1_data[i * mat1_size1 + j] = binaryAddInt(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (int32_t*)value1;
}

float* binaryAddFloatMat(float* value1, float* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  float* mat1_data = (float*)(((int32_t*)value1) + 2);
  float* mat2_data = (float*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      mat1_data[i * mat1_size1 + j] = binaryAddFloat(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (float*)value1;
}

int32_t* binarySubIntMat(int32_t* value1, int32_t* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  int32_t* mat1_data = (int32_t*)(((int32_t*)value1) + 2);
  int32_t* mat2_data = (int32_t*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      mat1_data[i * mat1_size1 + j] = binarySubInt(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (int32_t*)value1;
}

float* binarySubFloatMat(float* value1, float* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  float* mat1_data = (float*)(((int32_t*)value1) + 2);
  float* mat2_data = (float*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      mat1_data[i * mat1_size1 + j] = binarySubFloat(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (float*)value1;
}

int32_t* binaryMulIntMat(int32_t* value1, int32_t* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  int32_t* mat1_data = (int32_t*)(((int32_t*)value1) + 2);
  int32_t* mat2_data = (int32_t*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      mat1_data[i * mat1_size1 + j] = binaryMulInt(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (int32_t*)value1;
}

float* binaryMulFloatMat(float* value1, float* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  float* mat1_data = (float*)(((int32_t*)value1) + 2);
  float* mat2_data = (float*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      mat1_data[i * mat1_size1 + j] = binaryMulFloat(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (float*)value1;
}

int32_t* binaryDivIntMat(int32_t* value1, int32_t* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  int32_t* mat1_data = (int32_t*)(((int32_t*)value1) + 2);
  int32_t* mat2_data = (int32_t*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      mat1_data[i * mat1_size1 + j] = binaryDivInt(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (int32_t*)value1;
}

float* binaryDivFloatMat(float* value1, float* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  float* mat1_data = (float*)(((int32_t*)value1) + 2);
  float* mat2_data = (float*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      mat1_data[i * mat1_size1 + j] = binaryDivFloat(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (float*)value1;
}

int32_t* binaryModIntMat(int32_t* value1, int32_t* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  int32_t* mat1_data = (int32_t*)(((int32_t*)value1) + 2);
  int32_t* mat2_data = (int32_t*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      mat1_data[i * mat1_size1 + j] = binaryModInt(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (int32_t*)value1;
}

float* binaryModFloatMat(float* value1, float* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  float* mat1_data = (float*)(((int32_t*)value1) + 2);
  float* mat2_data = (float*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      mat1_data[i * mat1_size1 + j] = binaryModFloat(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (float*)value1;
}

int32_t* binaryExpIntMat(int32_t* value1, int32_t* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  int32_t* mat1_data = (int32_t*)(((int32_t*)value1) + 2);
  int32_t* mat2_data = (int32_t*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      mat1_data[i * mat1_size1 + j] = binaryExpInt(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (int32_t*)value1;
}

float* binaryExpFloatMat(float* value1, float* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  float* mat1_data = (float*)(((int32_t*)value1) + 2);
  float* mat2_data = (float*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      mat1_data[i * mat1_size1 + j] = binaryExpFloat(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (float*)value1;
}

bool* binaryLTIntMat(int32_t* value1, int32_t* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  int32_t* mat1_data = (int32_t*)(((int32_t*)value1) + 2);
  int32_t* mat2_data = (int32_t*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      ((bool*)mat1_data)[i * mat1_size1 + j] = binaryLTInt(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (bool*)value1;
}

bool* binaryLTFloatMat(float* value1, float* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  float* mat1_data = (float*)(((int32_t*)value1) + 2);
  float* mat2_data = (float*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      ((bool*)mat1_data)[i * mat1_size1 + j] = binaryLTFloat(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (bool*)value1;
}

bool* binaryLEIntMat(int32_t* value1, int32_t* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  int32_t* mat1_data = (int32_t*)(((int32_t*)value1) + 2);
  int32_t* mat2_data = (int32_t*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      ((bool*)mat1_data)[i * mat1_size1 + j] = binaryLEInt(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (bool*)value1;
}

bool* binaryLEFloatMat(float* value1, float* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  float* mat1_data = (float*)(((int32_t*)value1) + 2);
  float* mat2_data = (float*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      ((bool*)mat1_data)[i * mat1_size1 + j] = binaryLEFloat(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (bool*)value1;
}

bool* binaryGTIntMat(int32_t* value1, int32_t* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  int32_t* mat1_data = (int32_t*)(((int32_t*)value1) + 2);
  int32_t* mat2_data = (int32_t*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      ((bool*)mat1_data)[i * mat1_size1 + j] = binaryGTInt(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (bool*)value1;
}

bool* binaryGTFloatMat(float* value1, float* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  float* mat1_data = (float*)(((int32_t*)value1) + 2);
  float* mat2_data = (float*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      ((bool*)mat1_data)[i * mat1_size1 + j] = binaryGTFloat(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (bool*)value1;
}

bool* binaryGEIntMat(int32_t* value1, int32_t* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  int32_t* mat1_data = (int32_t*)(((int32_t*)value1) + 2);
  int32_t* mat2_data = (int32_t*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      ((bool*)mat1_data)[i * mat1_size1 + j] = binaryGEInt(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (bool*)value1;
}

bool* binaryGEFloatMat(float* value1, float* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  float* mat1_data = (float*)(((int32_t*)value1) + 2);
  float* mat2_data = (float*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      ((bool*)mat1_data)[i * mat1_size1 + j] = binaryGEFloat(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (bool*)value1;
}

bool binaryEQIntMat(int32_t* value1, int32_t* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  int32_t* mat1_data = (int32_t*)(((int32_t*)value1) + 2);
  int32_t* mat2_data = (int32_t*)(((int32_t*)value2) + 2);
  bool ret = true;
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      ret &= binaryEQInt(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return ret;
}

bool binaryEQFloatMat(float* value1, float* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  float* mat1_data = (float*)(((int32_t*)value1) + 2);
  float* mat2_data = (float*)(((int32_t*)value2) + 2);
  bool ret = true;
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      ret &= binaryEQFloat(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return ret;
}

bool binaryEQBoolMat(bool* value1, bool* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  bool* mat1_data = (bool*)(((int32_t*)value1) + 2);
  bool* mat2_data = (bool*)(((int32_t*)value2) + 2);
  bool ret = true;
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      ret &= binaryEQBool(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return ret;
}

bool binaryNEIntMat(int32_t* value1, int32_t* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  float* mat1_data = (float*)(((int32_t*)value1) + 2);
  float* mat2_data = (float*)(((int32_t*)value2) + 2);
  bool ret = false;
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      ret |= binaryNEInt(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return ret;
}

bool binaryNEFloatMat(float* value1, float* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  float* mat1_data = (float*)(((int32_t*)value1) + 2);
  float* mat2_data = (float*)(((int32_t*)value2) + 2);
  bool ret = false;
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      ret |= binaryNEFloat(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return ret;
}

bool binaryNEBoolMat(bool* value1, bool* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  bool* mat1_data = (bool*)(((int32_t*)value1) + 2);
  bool* mat2_data = (bool*)(((int32_t*)value2) + 2);
  bool ret = false;
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      ret |= binaryNEBool(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return ret;
}

bool* binaryAndBoolMat(bool* value1, bool* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  bool* mat1_data = (bool*)(((int32_t*)value1) + 2);
  bool* mat2_data = (bool*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      mat1_data[i * mat1_size1 + j] = binaryAndBool(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (bool*)value1;
}

bool* binaryOrBoolMat(bool* value1, bool* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  bool* mat1_data = (bool*)(((int32_t*)value1) + 2);
  bool* mat2_data = (bool*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      mat1_data[i * mat1_size1 + j] = binaryOrBool(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (bool*)value1;
}

bool* binaryXorBoolMat(bool* value1, bool* value2) {
  int32_t mat1_size0 = *((int32_t*)value1);
  int32_t mat1_size1 = *(((int32_t*)value1) + 1);
  int32_t mat2_size0 = *((int32_t*)value2);
  int32_t mat2_size1 = *(((int32_t*)value2) + 1);

  if (mat1_size0 != mat2_size0 || mat1_size1 != mat2_size1) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  bool* mat1_data = (bool*)(((int32_t*)value1) + 2);
  bool* mat2_data = (bool*)(((int32_t*)value2) + 2);
  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      mat1_data[i * mat1_size1 + j] = binaryXorBool(mat1_data[i * mat1_size1 + j], mat2_data[i * mat2_size1 + j]);
    }
  }
  free(value2);
  return (bool*)value1;
}

/* Interval Binary Operations*/
// TODO: Implement

struct Interval* binaryAddInterval(struct Interval* value1, struct Interval* value2) {
  struct Interval* interval = value1;
  interval->min = value1->min + value2->min;
  interval->max = value1->max + value2->max;
  free(value2);
  return interval;
}

struct Interval* binarySubInterval(struct Interval* value1, struct Interval* value2) {
  struct Interval* interval = value1;
  interval->min = value1->min - value2->min;
  interval->max = value1->max - value2->max;
  free(value2);
  return interval;
}

struct Interval* binaryMulInterval(struct Interval* value1, struct Interval* value2) {
  
}

bool binaryEQInterval(struct Interval* value1, struct Interval* value2) {
  return (value1->min == value2->min) && (value1->max == value2->max);
}

bool binaryNEInterval(struct Interval* value1, struct Interval* value2) {
  return (value1->min != value2->min) || (value1->max != value2->max);
}

/* Vector Only Operations*/

int32_t* concatIntVec(int32_t* value1, int32_t* value2) {
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  int32_t new_size = vec1_size + vec2_size;

  int32_t* vec1_data = (int32_t*)(((int32_t*)value1) + 1);
  int32_t* vec2_data = (int32_t*)(((int32_t*)value2) + 1);
  
  int32_t* ret = malloc(sizeof(int32_t) * (new_size) + sizeof(int32_t));
  int32_t* ret_data = (int32_t*)(ret + 1);
  *ret = new_size;

  memcpy(ret_data, vec1_data, vec1_size);
  memcpy(ret_data + vec1_size, vec2_data, vec2_size);
  return (int32_t*)ret;
}

float* concatFloatVec(float* value1, float* value2) {
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  int32_t new_size = vec1_size + vec2_size;

  float* vec1_data = (float*)(((int32_t*)value1) + 1);
  float* vec2_data = (float*)(((int32_t*)value2) + 1);
  
  int32_t* ret = malloc(sizeof(float) * (new_size) + sizeof(int32_t));
  float* ret_data = (float*)(ret + 1);
  *ret = new_size;

  memcpy(ret_data, vec1_data, vec1_size);
  memcpy(ret_data + vec1_size, vec2_data, vec2_size);
  return (float*)ret;
}

int8_t* concatCharVec(int8_t* value1, int8_t* value2) {
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  int32_t new_size = vec1_size + vec2_size;

  int8_t* vec1_data = (int8_t*)(((int32_t*)value1) + 1);
  int8_t* vec2_data = (int8_t*)(((int32_t*)value2) + 1);
  
  int32_t* ret = malloc(sizeof(int8_t) * (new_size) + sizeof(int32_t));
  int8_t* ret_data = (int8_t*)(ret + 1);
  *ret = new_size;

  memcpy(ret_data, vec1_data, vec1_size);
  memcpy(ret_data + vec1_size, vec2_data, vec2_size);
  return (int8_t*)ret;
}

bool* concatBoolVec(bool* value1, bool* value2) {
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);
  int32_t new_size = vec1_size + vec2_size;

  bool* vec1_data = (bool*)(((int32_t*)value1) + 1);
  bool* vec2_data = (bool*)(((int32_t*)value2) + 1);
  
  int32_t* ret = malloc(sizeof(bool) * (new_size) + sizeof(int32_t));
  bool* ret_data = (bool*)(ret + 1);
  *ret = new_size;

  memcpy(ret_data, vec1_data, vec1_size);
  memcpy(ret_data + vec1_size, vec2_data, vec2_size);
  return (bool*)ret;
}

int8_t* concatString(int8_t* string1, int8_t* string2) {
  return concatCharVec(string1, string2);
} 

int32_t dotIntVec(int32_t* value1, int32_t* value2) {
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);

 if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  int32_t* vec1_data = (int32_t*)(((int32_t*)value1) + 1);
  int32_t* vec2_data = (int32_t*)(((int32_t*)value2) + 1);

  int32_t accumulate = 0;
  for (int i = 0; i < vec1_size; i++) {
    int32_t product = binaryMulInt(vec1_data[i], vec2_data[i]);
    accumulate = binaryAddInt(accumulate, product); 
  }

  free(value1);
  free(value2);

  return accumulate;
}

float dotFloatVec(float* value1, float* value2) {
  int32_t vec1_size = *((int32_t*)value1);
  int32_t vec2_size = *((int32_t*)value2);

 if (vec1_size != vec2_size) {
    vectorSizeMismatchError(vec1_size, vec2_size);
  }

  float* vec1_data = (float*)(((int32_t*)value1) + 1);
  float* vec2_data = (float*)(((int32_t*)value2) + 1);

  float accumulate = 0;
  for (int i = 0; i < vec1_size; i++) {
    int32_t product = binaryMulFloat(vec1_data[i], vec2_data[i]);
    accumulate = binaryAddFloat(accumulate, product); 
  }

  free(value1);
  free(value2);

  return accumulate;
}

int32_t* dotIntMat(int32_t* matrix1, int32_t* matrix2) {
  int32_t mat1_size0 = *((int32_t*)matrix1);
  int32_t mat1_size1 = *(((int32_t*)matrix1) + 1);
  int32_t mat2_size0 = *((int32_t*)matrix2);
  int32_t mat2_size1 = *(((int32_t*)matrix2) + 1);

  if (mat1_size1 != mat2_size0) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  int32_t* mat1_data = (int32_t*)(((int32_t*)matrix1) + 2);
  int32_t* mat2_data = (int32_t*)(((int32_t*)matrix2) + 2);

  int32_t* ret = malloc(mat1_size0 * mat2_size1 * sizeof(int32_t) + 2 * sizeof(int32_t) );
  int32_t* ret_data = (int32_t*)(ret + 2);
  ret[0] = mat1_size0;
  ret[1] = mat2_size1;

  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      int32_t accumulate = 0;
      for (int k = 0; k < mat1_size1; k++) {
        int32_t product = binaryMulInt(mat1_data[i * mat1_size1 + k], mat2_data[k * mat2_size1 + j]);
        accumulate = binaryAddInt(accumulate, product); 
      }
      ret_data[i * mat1_size1 + j] = accumulate;
    }
  }
  free(matrix1);
  free(matrix2);

  return (int32_t*)ret;
}

float* dotFloatMat(float* matrix1, float* matrix2) {
  int32_t mat1_size0 = *((int32_t*)matrix1);
  int32_t mat1_size1 = *(((int32_t*)matrix1) + 1);
  int32_t mat2_size0 = *((int32_t*)matrix2);
  int32_t mat2_size1 = *(((int32_t*)matrix2) + 1);

  if (mat1_size1 != mat2_size0) {
    matrixSizeMismatchError(mat1_size0, mat1_size1, mat2_size0, mat2_size1);
  }

  float* mat1_data = (float*)(((int32_t*)matrix1) + 2);
  float* mat2_data = (float*)(((int32_t*)matrix2) + 2);

  int32_t* ret = malloc(mat1_size0 * mat2_size1 * sizeof(float) + 2 * sizeof(int32_t) );
  float* ret_data = (float*)(ret + 2);
  ret[0] = mat1_size0;
  ret[1] = mat2_size1;

  for (int i = 0; i < mat1_size0; i++) {
    for (int j = 0; j < mat1_size1; j++) {
      float accumulate = 0;
      for (int k = 0; k < mat1_size1; k++) {
        float product = binaryMulFloat(mat1_data[i * mat1_size1 + k], mat2_data[k * mat2_size1 + j]);
        accumulate = binaryAddFloat(accumulate, product); 
      }
      ret_data[i * mat1_size1 + j] = accumulate;
    }
  }
  free(matrix1);
  free(matrix2);

  return (float*)ret;
}

int32_t* byIntVec(int32_t* vector, int32_t by_value) {
  int32_t size = *((int32_t*)vector);
  int32_t new_size = size / by_value + (size % by_value ? 1 : 0);

  int32_t* vec_data = (int32_t*)(((int32_t*)vector) + 1);

  // malloc max size in new vector
  int32_t* ret = malloc(sizeof(int32_t) * new_size + sizeof(int32_t));
  *ret = new_size;
  int32_t* data = (int32_t*)(ret + 1);
  for (int i = 0; i < new_size; i++) {
    data[i] = vec_data[i * by_value];
  }

  return (int32_t*)ret;
}

float* byFloatVec(float* vector, int32_t by_value) {
  int32_t size = *((int32_t*)vector);
  int32_t new_size = size / by_value + (size % by_value ? 1 : 0);

  float* vec_data = (float*)(((int32_t*)vector) + 1);

  // malloc max size in new vector
  int32_t* ret = malloc(sizeof(float) * new_size + sizeof(int32_t));
  *ret = new_size;
  float* data = (float*)(ret + 1);
  for (int i = 0; i < new_size; i++) {
    data[i] = vec_data[i * by_value];
  }

  return (float*)ret;
}
int8_t* byCharVec(int8_t* vector, int32_t by_value) {
  int32_t size = *((int32_t*)vector);
  int32_t new_size = size / by_value + (size % by_value ? 1 : 0);

  int8_t* vec_data = (int8_t*)(((int32_t*)vector) + 1);

  // malloc max size in new vector
  int32_t* ret = malloc(sizeof(int8_t) * new_size + sizeof(int32_t));
  *ret = new_size;
  int8_t* data = (int8_t*)(ret + 1);
  for (int i = 0; i < new_size; i++) {
    data[i] = vec_data[i * by_value];
  }

  return (int8_t*)ret;
}
bool* byBoolVec(bool* vector, int32_t by_value) {
  int32_t size = *((int32_t*)vector);
  int32_t new_size = size / by_value + (size % by_value ? 1 : 0);

  bool* vec_data = (bool*)(((int32_t*)vector) + 1);

  // malloc max size in new vector
  int32_t* ret = malloc(sizeof(bool) * new_size + sizeof(int32_t));
  *ret = new_size;
  bool* data = (bool*)(ret + 1);
  for (int i = 0; i < new_size; i++) {
    data[i] = vec_data[i * by_value];
  }

  return (bool*)ret;
}

int32_t* byInterval(struct Interval* interval, int32_t by_value) {
  int32_t size = interval->max - interval->min + 1;
  int32_t new_size = size / by_value + (size % by_value ? 1 : 0);

  int32_t* ret = malloc(sizeof(int32_t) * new_size + sizeof(int32_t));
  *ret = new_size;
  int32_t* data = (int32_t*)(ret + 1);

  for (int i = 0; i < new_size; i++) {
    data[i] = interval->min + by_value * i;
  }
  free(interval);
  return (int32_t*)ret;
}
