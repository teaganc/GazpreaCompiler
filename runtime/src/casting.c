#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "errors.h"

/* Scalar to Vector Functions*/

bool* castBoolBoolVec(bool value, int32_t size) { 
  int32_t* ret = malloc(sizeof(bool) * size + sizeof(int32_t));
  bool* data = (bool*) (ret + 1);
  if (size == -1) {
    size = 1;
  }
  ret[0] = size;
  for (int i = 0; i < size; i++) {
    data[i] = value;
  }
  return (bool*)ret;
}

int32_t* castIntIntVec(int32_t value, int32_t size) { 
  int32_t* ret = malloc(sizeof(int32_t) * size + sizeof(int32_t));
  int32_t* data = (int32_t*) (ret + 1);
  if (size == -1) {
    size = 1;
  }
  ret[0] = size;
  for (int i = 0; i < size; i++) {
    data[i] = value;
  }
  return (int32_t*)ret;
}

int8_t* castCharCharVec(int8_t value, int32_t size) { 
  int32_t* ret = malloc(sizeof(int8_t) * size + sizeof(int32_t));
  int8_t* data = (char*) (ret + 1);
  if (size == -1) {
    size = 1;
  }
  ret[0] = size;
  for (int i = 0; i < size; i++) {
    data[i] = value;
  }
  return (int8_t*)ret;
}

float* castFloatFloatVec(float value, int32_t size) { 
  int32_t* ret = malloc(sizeof(float) * size + sizeof(int32_t));
  float* data = (float*) (ret + 1);
  if (size == -1) {
    size = 1;
  }
  ret[0] = size;
  for (int i = 0; i < size; i++) {
    data[i] = value;
  }
  return (float*)ret;
}

/* Scalar to Matrix Functions*/

bool* castBoolBoolMat(bool value, int32_t size0, int32_t size1) { 
  int32_t* ret = malloc(sizeof(bool) * size0 * size1 + 2 * sizeof(int32_t));
  bool* data = (bool*) (ret + 2);
  if (size0 == -1) {
    size0 = 1;
  }
  if (size1 == -1) {
    size1 = 1;
  }
  ret[0] = size0;
  ret[1] = size1;

  for (int i = 0; i < size0; i++) {
    for (int j = 0; j < size1; j++) {
      data[i * size1 + j];
    }
  }
  return (bool*)ret;
}

int32_t* castIntIntMat(int32_t value, int32_t size0, int32_t size1) { 
  int32_t* ret = malloc(sizeof(int32_t) * size0 * size1 + 2 * sizeof(int32_t));
  int32_t* data = (int32_t*) (ret + 2);
  if (size0 == -1) {
    size0 = 1;
  }
  if (size1 == -1) {
    size1 = 1;
  }
  ret[0] = size0;
  ret[1] = size1;

  for (int i = 0; i < size0; i++) {
    for (int j = 0; j < size1; j++) {
      data[i * size1 + j];
    }
  }
  return (int32_t*)ret;
}

int8_t* castCharCharMat(int8_t value, int32_t size0, int32_t size1) { 
  int32_t* ret = malloc(sizeof(int8_t) * size0 * size1 + 2 * sizeof(int32_t));
  int8_t* data = (int8_t*) (ret + 2);
  if (size0 == -1) {
    size0 = 1;
  }
  if (size1 == -1) {
    size1 = 1;
  }
  ret[0] = size0;
  ret[1] = size1;

  for (int i = 0; i < size0; i++) {
    for (int j = 0; j < size1; j++) {
      data[i * size1 + j];
    }
  }
  return (int8_t*)ret;
}

float* castFloatFloatMat(float value, int32_t size0, int32_t size1) { 
  int32_t* ret = malloc(sizeof(float) * size0 * size1 + 2 * sizeof(int32_t));
  float* data = (float*) (ret + 2);
  if (size0 == -1) {
    size0 = 1;
  }
  if (size1 == -1) {
    size1 = 1;
  }
  ret[0] = size0;
  ret[1] = size1;

  for (int i = 0; i < size0; i++) {
    for (int j = 0; j < size1; j++) {
      data[i * size1 + j];
    }
  }
  return (float*)ret;
}

/* Scalar Casting*/

// boolean value casting
bool castBoolBool(bool value) { return value; }

int32_t castBoolChar(bool value) { return value; }

int8_t castBoolInt(bool value) { return value; }

float castBoolFloat(bool value) { return value; }

// integer value casting
bool castIntBool(int32_t value) { return value; }

int32_t castIntInt(int32_t value) { return value; }

int8_t castIntChar(int32_t value) { return value; }

float castIntFloat(int32_t value) { return value; }

// character value casting
bool castCharBool(int8_t value) { return value; }

int32_t castCharInt(int8_t value) { return value; }

int8_t castCharChar(int8_t value) { return value; }

float castCharFloat(int8_t value) { return value; }

// real value casting
int32_t castFloatInt(float value) { return value; }

float castFloatFloat(float value) { return value; }

/* Vector to Vector Casting*/
int32_t* castNoneVecIntVec(int32_t* pointer, int32_t new_size) {
  int32_t* old_data = (int32_t*)(((int32_t*)pointer)+1);
  int32_t old_size = *(int32_t*)pointer;

  if (new_size == -1) {
    new_size = old_size;
  }

  int32_t* ret_pointer = malloc(new_size * sizeof(int32_t) + sizeof(int32_t));
  int32_t* new_data = (int32_t*)(((int32_t*)ret_pointer)+1);


  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    new_data[i-1] = i <= old_size ? old_data[i-1] : 0;
  }

  free(pointer);
  return ret_pointer;
}

bool* castNoneVecBoolVec(int32_t* pointer, int32_t new_size) {
  int32_t* old_data = (int32_t*)(((int32_t*)pointer)+1);
  int32_t old_size = *(int32_t*)pointer;

  if (new_size == -1) {
    new_size = old_size;
  }
  bool* ret_pointer = malloc(new_size * sizeof(bool) + sizeof(int32_t));
  bool* new_data = (bool*)(((int32_t*)ret_pointer)+1);

  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    new_data[i-1] = i <= old_size ? old_data[i-1] : 0;
  }

  free(pointer);
  return ret_pointer;
}

int8_t* castNoneVecCharVec(int32_t* pointer, int32_t new_size) {
  int32_t* old_data = (int32_t*)(((int32_t*)pointer)+1);
  int32_t old_size = *(int32_t*)pointer;

  if (new_size == -1) {
    new_size = old_size;
  }
  
  int8_t* ret_pointer = malloc(new_size * sizeof(int8_t) + sizeof(int32_t));
  int8_t* new_data = (int8_t*)(((int32_t*)ret_pointer)+1);

  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    new_data[i-1] = i <= old_size ? old_data[i-1] : 0;
  }

  free(pointer);
  return ret_pointer;
}

float* castNoneVecFloatVec(int32_t* pointer, int32_t new_size) {
  int32_t* old_data = (int32_t*)(((int32_t*)pointer)+1);
  int32_t old_size = *(int32_t*)pointer;

  if (new_size == -1) {
    new_size = old_size;
  }

  float* ret_pointer = malloc(new_size * sizeof(float) + sizeof(int32_t));
  float* new_data = (float*)(((int32_t*)ret_pointer)+1);

  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    new_data[i-1] = i <= old_size ? old_data[i-1] : 0;
  }

  free(pointer);
  return ret_pointer;
}

bool* castBoolVecBoolVec(bool* pointer, int32_t new_size) {
  bool* old_data = (bool*)(((int32_t*)pointer)+1);
  int32_t old_size = *(int32_t*)pointer;
  
  if (new_size == -1) {
    new_size = old_size;
  }

  bool* ret_pointer = malloc(new_size * sizeof(bool) + sizeof(int32_t));
  bool* new_data = (bool*)(((int32_t*)ret_pointer)+1);

  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    new_data[i-1] = i <= old_size ? old_data[i-1] : 0;
  }

  free(pointer);
  return ret_pointer;
}
int32_t* castBoolVecIntVec(bool* pointer, int32_t new_size) {
  bool* old_data = (bool*)(((int32_t*)pointer)+1);
  int32_t old_size = *(int32_t*)pointer;
  
  if (new_size == -1) {
    new_size = old_size;
  }

  int32_t* ret_pointer = malloc(new_size * sizeof(int32_t) + sizeof(int32_t));
  int32_t* new_data = (int32_t*)(((int32_t*)ret_pointer)+1);

  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    new_data[i-1] = i <= old_size ? old_data[i-1] : 0;
  }

  free(pointer);
  return ret_pointer;
}
int8_t* castBoolVecCharVec(bool* pointer, int32_t new_size) {
  bool* old_data = (bool*)(((int32_t*)pointer)+1);
  int32_t old_size = *(int32_t*)pointer;

  if (new_size == -1) {
    new_size = old_size;
  }

  int8_t* ret_pointer = malloc(new_size * sizeof(int8_t) + sizeof(int32_t));
  int8_t* new_data = (int8_t*)(((int32_t*)ret_pointer)+1);

  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    new_data[i-1] = i <= old_size ? old_data[i-1] : 0;
  }

  free(pointer);
  return ret_pointer;
}
float* castBoolVecFloatVec(bool* pointer, int32_t new_size) {
  bool* old_data = (bool*)(((int32_t*)pointer)+1);
  int32_t old_size = *(int32_t*)pointer;
  
  if (new_size == -1) {
    new_size = old_size;
  }
  
  float* ret_pointer = malloc(new_size * sizeof(float) + sizeof(int32_t));
  float* new_data = (float*)(((int32_t*)ret_pointer)+1);

  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    new_data[i-1] = i <= old_size ? old_data[i-1] : 0;
  }

  free(pointer);
  return ret_pointer;
}

bool* castIntVecBoolVec(int32_t* pointer, int32_t new_size) {
  int32_t* old_data = (int32_t*)(((int32_t*)pointer)+1);
  int32_t old_size = *(int32_t*)pointer;

  if (new_size == -1) {
    new_size = old_size;
  }

  bool* ret_pointer = malloc(new_size * sizeof(bool) + sizeof(int32_t));
  bool* new_data = (bool*)(((int32_t*)ret_pointer)+1);

  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    new_data[i-1] = i <= old_size ? old_data[i-1] : 0;
  }

  free(pointer);
  return ret_pointer;
}
int32_t* castIntVecIntVec(int32_t* pointer, int32_t new_size) {
  int32_t* old_data = (int32_t*)(((int32_t*)pointer)+1);
  int32_t old_size = *(int32_t*)pointer;

  if (new_size == -1) {
    new_size = old_size;
  }
  
  int32_t* ret_pointer = malloc(new_size * sizeof(int32_t) + sizeof(int32_t));
  int32_t* new_data = (int32_t*)(((int32_t*)ret_pointer)+1);

  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    new_data[i-1] = i <= old_size ? old_data[i-1] : 0;
  }

  free(pointer);
  return ret_pointer;
}
int8_t* castIntVecCharVec(int32_t* pointer, int32_t new_size) {
  int32_t* old_data = (int32_t*)(((int32_t*)pointer)+1);
  int32_t old_size = *(int32_t*)pointer;
  
  if (new_size == -1) {
    new_size = old_size;
  }
  
  int8_t* ret_pointer = malloc(new_size * sizeof(int8_t) + sizeof(int32_t));
  int8_t* new_data = (int8_t*)(((int32_t*)ret_pointer)+1);

  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    new_data[i-1] = i <= old_size ? old_data[i-1] : 0;
  }

  free(pointer);
  return ret_pointer;
}
float* castIntVecFloatVec(int32_t* pointer, int32_t new_size) {
  int32_t* old_data = (int32_t*)(((int32_t*)pointer)+1);
  int32_t old_size = *(int32_t*)pointer;

  if (new_size == -1) {
    new_size = old_size;
  }
  
  float* ret_pointer = malloc(new_size * sizeof(float) + sizeof(int32_t));
  float* new_data = (float*)(((int32_t*)ret_pointer)+1);

  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    new_data[i-1] = i <= old_size ? old_data[i-1] : 0;
  }

  free(pointer);
  return ret_pointer;
}

bool* castCharVecBoolVec(int8_t* pointer, int32_t new_size) {
  int8_t* old_data = (int8_t*)(((int32_t*)pointer)+1);
  int32_t old_size = *(int32_t*)pointer;
  
  if (new_size == -1) {
    new_size = old_size;
  }
  
  bool* ret_pointer = malloc(new_size * sizeof(bool) + sizeof(int32_t));
  bool* new_data = (bool*)(((int32_t*)ret_pointer)+1);

  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    new_data[i-1] = i <= old_size ? old_data[i-1] : 0;
  }

  free(pointer);
  return ret_pointer;
}
int32_t* castCharVecIntVec(int8_t* pointer, int32_t new_size) {
  int8_t* old_data = (int8_t*)(((int32_t*)pointer)+1);
  int32_t old_size = *(int32_t*)pointer;
  
  if (new_size == -1) {
    new_size = old_size;
  }

  int32_t* ret_pointer = malloc(new_size * sizeof(int32_t) + sizeof(int32_t));
  int32_t* new_data = (int32_t*)(((int32_t*)ret_pointer)+1);

  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    new_data[i-1] = i <= old_size ? old_data[i-1] : 0;
  }

  free(pointer);
  return ret_pointer;
}
int8_t* castCharVecCharVec(int8_t* pointer, int32_t new_size) {
  int8_t* old_data = (int8_t*)(((int32_t*)pointer)+1);
  int32_t old_size = *(int32_t*)pointer;
  
  if (new_size == -1) {
    new_size = old_size;
  } 
  int8_t* ret_pointer = malloc(new_size * sizeof(int8_t) + sizeof(int32_t));
  int8_t* new_data = (int8_t*)(((int32_t*)ret_pointer)+1);

  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    new_data[i-1] = i <= old_size ? old_data[i-1] : 0;
  }

  free(pointer);
  return ret_pointer;
}
float* castCharVecFloatVec(int8_t* pointer, int32_t new_size) {
  int8_t* old_data = (int8_t*)(((int32_t*)pointer)+1);
  int32_t old_size = *(int32_t*)pointer;
  
  if (new_size == -1) {
    new_size = old_size;
  }
  
  float* ret_pointer = malloc(new_size * sizeof(float) + sizeof(int32_t));
  float* new_data = (float*)(((int32_t*)ret_pointer)+1);

  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    new_data[i-1] = i <= old_size ? old_data[i-1] : 0;
  }

  free(pointer);
  return ret_pointer;
}

int32_t* castFloatVecIntVec(float* pointer, int32_t new_size) {
  float* old_data = (float*)(((int32_t*)pointer)+1);
  int32_t old_size = *(int32_t*)pointer;
  
  if (new_size == -1) {
    new_size = old_size;
  }
  int32_t* ret_pointer = malloc(new_size * sizeof(int32_t) + sizeof(int32_t));
  int32_t* new_data = (int32_t*)(((int32_t*)ret_pointer)+1);

  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    new_data[i-1] = i <= old_size ? old_data[i-1] : 0;
  }

  free(pointer);
  return ret_pointer;
}
float* castFloatVecFloatVec(float* pointer, int32_t new_size) {
  float* old_data = (float*)(((int32_t*)pointer)+1);
  int32_t old_size = *(int32_t*)pointer;
  
  if (new_size == -1) {
    new_size = old_size;
  }

  float* ret_pointer = malloc(new_size * sizeof(float) + sizeof(int32_t));
  float* new_data = (float*)(((int32_t*)ret_pointer)+1);

  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    new_data[i-1] = i <= old_size ? old_data[i-1] : 0;
  }

  free(pointer);
  return ret_pointer;
}

/*
float* castCharVecFloatVec(char* pointer, int32_t new_size) {
  int32_t old_size = *(int32_t*)pointer;
  float* ret_pointer = pointer;
  char* old_data = (char*)(((int32_t*)ret_pointer)+1);
  float* new_data = (float*)old_data;

  if (sizeof(char) * old_size < sizeof(float) * new_size || sizeof(char) > sizeof(float)) {
    ret_pointer = malloc(new_size * sizeof(float) + sizeof(int32_t));
    new_data = (float*)(((int32_t*)ret_pointer)+1);
  }

  *(int32_t*)ret_pointer = new_size;
  for (int i = new_size; i; --i) {
    if (i > old_size) {
      new_data[i-1] = 0;
    }
    else {
      new_data[i-1] = old_data[i-1];
    }
  }

  if (sizeof(char) * old_size < sizeof(float) * new_size) {
    free(pointer);
  }
  return ret_pointer;
}
*/
/* Matrix to Matrix Casting*/
int32_t* castNoneVecIntMat(int32_t* pointer, int32_t new_size1, int32_t new_size2) {
  int32_t* old_data = (int32_t*)(((int32_t*)pointer)+2);
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);

  if (new_size1 == -1) {
    new_size1 = old_size1;
  }
  if (new_size2 == -1) {
    new_size2 = old_size2;
  }

  int32_t* ret_pointer = malloc(new_size1 * new_size2 * sizeof(int32_t) + sizeof(int32_t) * 2);;
  int32_t* new_data = (int32_t*)(((int32_t*)ret_pointer)+2);

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)ret_pointer)+1) = new_size2;

  for (int i = 0; i < new_size1; i++) {
    for (int j = 0; j < new_size2; j++) {
      new_data[i * new_size2 + j] = (i < old_size1 && j < old_size2) ? old_data[i * old_size2 + j] : 0;
    }
  }
  free(pointer);
  return ret_pointer;
}
bool* castNoneVecBoolMat(int32_t* pointer, int32_t new_size1, int32_t new_size2) {
  int32_t* old_data = (int32_t*)(((int32_t*)pointer)+2);
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);

  if (new_size1 == -1) {
    new_size1 = old_size1;
  }
  if (new_size2 == -1) {
    new_size2 = old_size2;
  }
    
  bool* ret_pointer = malloc(new_size1 * new_size2 * sizeof(bool) + sizeof(int32_t) * 2);;
  bool* new_data = (bool*)(((int32_t*)ret_pointer)+2);

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)ret_pointer)+1) = new_size2;

  for (int i = 0; i < new_size1; i++) {
    for (int j = 0; j < new_size2; j++) {
      new_data[i * new_size2 + j] = (i < old_size1 && j < old_size2) ? old_data[i * old_size2 + j] : 0;
    }
  }
  free(pointer);
  return ret_pointer;
}

int8_t* castNoneVecCharMat(int32_t* pointer, int32_t new_size1, int32_t new_size2) {
  int32_t* old_data = (int32_t*)(((int32_t*)pointer)+2);
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);

  if (new_size1 == -1) {
    new_size1 = old_size1;
  }
  if (new_size2 == -1) {
    new_size2 = old_size2;
  }

  int8_t* ret_pointer = malloc(new_size1 * new_size2 * sizeof(int8_t) + sizeof(int32_t) * 2);;
  int8_t* new_data = (int8_t*)(((int32_t*)ret_pointer)+2);

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)ret_pointer)+1) = new_size2;

  for (int i = 0; i < new_size1; i++) {
    for (int j = 0; j < new_size2; j++) {
      new_data[i * new_size2 + j] = (i < old_size1 && j < old_size2) ? old_data[i * old_size2 + j] : 0;
    }
  }
  free(pointer);
  return ret_pointer;
}

float* castNoneVecFloatMat(int32_t* pointer, int32_t new_size1, int32_t new_size2) {
  int32_t* old_data = (int32_t*)(((int32_t*)pointer)+2);
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);

  if (new_size1 == -1) {
    new_size1 = old_size1;
  }
  if (new_size2 == -1) {
    new_size2 = old_size2;
  }
  
  float* ret_pointer = malloc(new_size1 * new_size2 * sizeof(float) + sizeof(int32_t) * 2);;
  float* new_data = (float*)(((int32_t*)ret_pointer)+2);

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)ret_pointer)+1) = new_size2;

  for (int i = 0; i < new_size1; i++) {
    for (int j = 0; j < new_size2; j++) {
      new_data[i * new_size2 + j] = (i < old_size1 && j < old_size2) ? old_data[i * old_size2 + j] : 0;
    }
  }
  free(pointer);
  return ret_pointer;
}

bool* castBoolMatBoolMat(bool* pointer, int32_t new_size1, int32_t new_size2) {
  bool* old_data = (bool*)(((int32_t*)pointer)+2);
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);

  if (new_size1 == -1) {
    new_size1 = old_size1;
  }
  if (new_size2 == -1) {
    new_size2 = old_size2;
  }

  bool* ret_pointer = malloc(new_size1 * new_size2 * sizeof(bool) + sizeof(int32_t) * 2);;
  bool* new_data = (bool*)(((int32_t*)ret_pointer)+2);

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)ret_pointer)+1) = new_size2;

  for (int i = 0; i < new_size1; i++) {
    for (int j = 0; j < new_size2; j++) {
      new_data[i * new_size2 + j] = (i < old_size1 && j < old_size2) ? old_data[i * old_size2 + j] : 0;
    }
  }
  free(pointer);
  return ret_pointer;
}
int32_t* castBoolMatIntMat(bool* pointer, int32_t new_size1, int32_t new_size2) {
  bool* old_data = (bool*)(((int32_t*)pointer)+2);
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);

  if (new_size1 == -1) {
    new_size1 = old_size1;
  }
  if (new_size2 == -1) {
    new_size2 = old_size2;
  }

  int32_t* ret_pointer = malloc(new_size1 * new_size2 * sizeof(int32_t) + sizeof(int32_t) * 2);;
  int32_t* new_data = (int32_t*)(((int32_t*)ret_pointer)+2);

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)ret_pointer)+1) = new_size2;

  for (int i = 0; i < new_size1; i++) {
    for (int j = 0; j < new_size2; j++) {
      new_data[i * new_size2 + j] = (i < old_size1 && j < old_size2) ? old_data[i * old_size2 + j] : 0;
    }
  }
  free(pointer);
  return ret_pointer;
}
int8_t* castBoolMatCharMat(bool* pointer, int32_t new_size1, int32_t new_size2) {
  bool* old_data = (bool*)(((int32_t*)pointer)+2);
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);

  if (new_size1 == -1) {
    new_size1 = old_size1;
  }
  if (new_size2 == -1) {
    new_size2 = old_size2;
  }
  
  int8_t* ret_pointer = malloc(new_size1 * new_size2 * sizeof(int8_t) + sizeof(int32_t) * 2);;
  int8_t* new_data = (int8_t*)(((int32_t*)ret_pointer)+2);

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)ret_pointer)+1) = new_size2;

  for (int i = 0; i < new_size1; i++) {
    for (int j = 0; j < new_size2; j++) {
      new_data[i * new_size2 + j] = (i < old_size1 && j < old_size2) ? old_data[i * old_size2 + j] : 0;
    }
  }
  free(pointer);
  return ret_pointer;
}
float* castBoolMatFloatMat(bool* pointer, int32_t new_size1, int32_t new_size2) {
  bool* old_data = (bool*)(((int32_t*)pointer)+2);
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);

  if (new_size1 == -1) {
    new_size1 = old_size1;
  }
  if (new_size2 == -1) {
    new_size2 = old_size2;
  }
  
  float* ret_pointer = malloc(new_size1 * new_size2 * sizeof(float) + sizeof(int32_t) * 2);;
  float* new_data = (float*)(((int32_t*)ret_pointer)+2);

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)ret_pointer)+1) = new_size2;

  for (int i = 0; i < new_size1; i++) {
    for (int j = 0; j < new_size2; j++) {
      new_data[i * new_size2 + j] = (i < old_size1 && j < old_size2) ? old_data[i * old_size2 + j] : 0;
    }
  }
  free(pointer);
  return ret_pointer;
}

bool* castIntMatBoolMat(int32_t* pointer, int32_t new_size1, int32_t new_size2) {
  int32_t* old_data = (int32_t*)(((int32_t*)pointer)+2);
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);

  if (new_size1 == -1) {
    new_size1 = old_size1;
  }
  if (new_size2 == -1) {
    new_size2 = old_size2;
  }
  
  bool* ret_pointer = malloc(new_size1 * new_size2 * sizeof(bool) + sizeof(int32_t) * 2);;
  bool* new_data = (bool*)(((int32_t*)ret_pointer)+2);

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)ret_pointer)+1) = new_size2;

  for (int i = 0; i < new_size1; i++) {
    for (int j = 0; j < new_size2; j++) {
      new_data[i * new_size2 + j] = (i < old_size1 && j < old_size2) ? old_data[i * old_size2 + j] : 0;
    }
  }
  free(pointer);
  return ret_pointer;
}
int32_t* castIntMatIntMat(int32_t* pointer, int32_t new_size1, int32_t new_size2) {
  int32_t* old_data = (int32_t*)(((int32_t*)pointer)+2);
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);
  
  if (new_size1 == -1) {
    new_size1 = old_size1;
  }
  if (new_size2 == -1) {
    new_size2 = old_size2;
  }

  int32_t* ret_pointer = malloc(new_size1 * new_size2 * sizeof(int32_t) + sizeof(int32_t) * 2);;
  int32_t* new_data = (int32_t*)(((int32_t*)ret_pointer)+2);

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)ret_pointer)+1) = new_size2;

  for (int i = 0; i < new_size1; i++) {
    for (int j = 0; j < new_size2; j++) {
      new_data[i * new_size2 + j] = (i < old_size1 && j < old_size2) ? old_data[i * old_size2 + j] : 0;
    }
  }
  free(pointer);
  return ret_pointer;
}
int8_t* castIntMatCharMat(int32_t* pointer, int32_t new_size1, int32_t new_size2) {
  int32_t* old_data = (int32_t*)(((int32_t*)pointer)+2);
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);

  if (new_size1 == -1) {
    new_size1 = old_size1;
  }
  if (new_size2 == -1) {
    new_size2 = old_size2;
  }
  
  int8_t* ret_pointer = malloc(new_size1 * new_size2 * sizeof(int8_t) + sizeof(int32_t) * 2);;
  int8_t* new_data = (int8_t*)(((int32_t*)ret_pointer)+2);

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)ret_pointer)+1) = new_size2;

  for (int i = 0; i < new_size1; i++) {
    for (int j = 0; j < new_size2; j++) {
      new_data[i * new_size2 + j] = (i < old_size1 && j < old_size2) ? old_data[i * old_size2 + j] : 0;
    }
  }
  free(pointer);
  return ret_pointer;
}
float* castIntMatFloatMat(int32_t* pointer, int32_t new_size1, int32_t new_size2) {
  int32_t* old_data = (int32_t*)(((int32_t*)pointer)+2);
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);

  if (new_size1 == -1) {
    new_size1 = old_size1;
  }
  if (new_size2 == -1) {
    new_size2 = old_size2;
  }
  
  float* ret_pointer = malloc(new_size1 * new_size2 * sizeof(float) + sizeof(int32_t) * 2);;
  float* new_data = (float*)(((int32_t*)ret_pointer)+2);

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)ret_pointer)+1) = new_size2;

  for (int i = 0; i < new_size1; i++) {
    for (int j = 0; j < new_size2; j++) {
      new_data[i * new_size2 + j] = (i < old_size1 && j < old_size2) ? old_data[i * old_size2 + j] : 0;
    }
  }
  free(pointer);
  return ret_pointer;
}

bool* castCharMatBoolMat(int8_t* pointer, int32_t new_size1, int32_t new_size2) {
  int8_t* old_data = (int8_t*)(((int32_t*)pointer)+2);
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);

  if (new_size1 == -1) {
    new_size1 = old_size1;
  }
  if (new_size2 == -1) {
    new_size2 = old_size2;
  }
  
  bool* ret_pointer = malloc(new_size1 * new_size2 * sizeof(bool) + sizeof(int32_t) * 2);;
  bool* new_data = (bool*)(((int32_t*)ret_pointer)+2);

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)ret_pointer)+1) = new_size2;

  for (int i = 0; i < new_size1; i++) {
    for (int j = 0; j < new_size2; j++) {
      new_data[i * new_size2 + j] = (i < old_size1 && j < old_size2) ? old_data[i * old_size2 + j] : 0;
    }
  }
  free(pointer);
  return ret_pointer;
}
int32_t* castCharMatIntMat(int8_t* pointer, int32_t new_size1, int32_t new_size2) {
  int8_t* old_data = (int8_t*)(((int32_t*)pointer)+2);
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);

  if (new_size1 == -1) {
    new_size1 = old_size1;
  }
  if (new_size2 == -1) {
    new_size2 = old_size2;
  }
  
  int32_t* ret_pointer = malloc(new_size1 * new_size2 * sizeof(int32_t) + sizeof(int32_t) * 2);;
  int32_t* new_data = (int32_t*)(((int32_t*)ret_pointer)+2);

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)ret_pointer)+1) = new_size2;

  for (int i = 0; i < new_size1; i++) {
    for (int j = 0; j < new_size2; j++) {
      new_data[i * new_size2 + j] = (i < old_size1 && j < old_size2) ? old_data[i * old_size2 + j] : 0;
    }
  }
  free(pointer);
  return ret_pointer;
}
int8_t* castCharMatCharMat(int8_t* pointer, int32_t new_size1, int32_t new_size2) {
  int8_t* old_data = (int8_t*)(((int32_t*)pointer)+2);
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);

  if (new_size1 == -1) {
    new_size1 = old_size1;
  }
  if (new_size2 == -1) {
    new_size2 = old_size2;
  }
  
  int8_t* ret_pointer = malloc(new_size1 * new_size2 * sizeof(int8_t) + sizeof(int32_t) * 2);;
  int8_t* new_data = (int8_t*)(((int32_t*)ret_pointer)+2);

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)ret_pointer)+1) = new_size2;

  for (int i = 0; i < new_size1; i++) {
    for (int j = 0; j < new_size2; j++) {
      new_data[i * new_size2 + j] = (i < old_size1 && j < old_size2) ? old_data[i * old_size2 + j] : 0;
    }
  }
  free(pointer);
  return ret_pointer;
}
float* castCharMatFloatMat(int8_t* pointer, int32_t new_size1, int32_t new_size2) {
  int8_t* old_data = (int8_t*)(((int32_t*)pointer)+2);
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);

  if (new_size1 == -1) {
    new_size1 = old_size1;
  }
  if (new_size2 == -1) {
    new_size2 = old_size2;
  }
  
  float* ret_pointer = malloc(new_size1 * new_size2 * sizeof(float) + sizeof(int32_t) * 2);;
  float* new_data = (float*)(((int32_t*)ret_pointer)+2);

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)ret_pointer)+1) = new_size2;

  for (int i = 0; i < new_size1; i++) {
    for (int j = 0; j < new_size2; j++) {
      new_data[i * new_size2 + j] = (i < old_size1 && j < old_size2) ? old_data[i * old_size2 + j] : 0;
    }
  }
  free(pointer);
  return ret_pointer;
}

int32_t* castFloatMatIntMat(float* pointer, int32_t new_size1, int32_t new_size2) {
  float* old_data = (float*)(((int32_t*)pointer)+2);
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);

  if (new_size1 == -1) {
    new_size1 = old_size1;
  }
  if (new_size2 == -1) {
    new_size2 = old_size2;
  }

  int32_t* ret_pointer = malloc(new_size1 * new_size2 * sizeof(int32_t) + sizeof(int32_t) * 2);;
  int32_t* new_data = (int32_t*)(((int32_t*)ret_pointer)+2);

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)ret_pointer)+1) = new_size2;

  for (int i = 0; i < new_size1; i++) {
    for (int j = 0; j < new_size2; j++) {
      new_data[i * new_size2 + j] = (i < old_size1 && j < old_size2) ? old_data[i * old_size2 + j] : 0;
    }
  }
  free(pointer);
  return ret_pointer;
}
float* castFloatMatFloatMat(float* pointer, int32_t new_size1, int32_t new_size2) {
  float* old_data = (float*)(((int32_t*)pointer)+2);
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);

  if (new_size1 == -1) {
    new_size1 = old_size1;
  }
  if (new_size2 == -1) {
    new_size2 = old_size2;
  }

  float* ret_pointer = malloc(new_size1 * new_size2 * sizeof(float) + sizeof(int32_t) * 2);;
  float* new_data = (float*)(((int32_t*)ret_pointer)+2);

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)ret_pointer)+1) = new_size2;

  for (int i = 0; i < new_size1; i++) {
    for (int j = 0; j < new_size2; j++) {
      new_data[i * new_size2 + j] = (i < old_size1 && j < old_size2) ? old_data[i * old_size2 + j] : 0;
    }
  }
  free(pointer);
  return ret_pointer;
}
/*
float* castCharMatFloatMat(char* pointer, int32_t new_size1, int32_t new_size2) {
  int32_t old_size1 = *(int32_t*)pointer;
  int32_t old_size2 = *(((int32_t*)pointer)+1);

  float* ret_pointer = pointer;
  char* old_data = (char*)(((int32_t*)ret_pointer)+2);
  float* new_data = (float*)old_data;

  if (sizeof(char) * old_size1 * old_size2 < sizeof(float) * new_size1 * new_size2 || sizeof(char) > sizeof(float)) {
    ret_pointer = malloc(new_size1 * new_size2 * sizeof(float) + sizeof(int32_t) * 2);
    new_data = (float*)(((int32_t*)ret_pointer)+2);
  }

  *(int32_t*)ret_pointer = new_size1;
  *(((int32_t*)pointer)+1) = new_size2;

  for (int i = new_size1; i; --i) {
    for (int j = new_size2; j; --j) {
      if (i > old_size1 || j > old_size2) {
        new_data[i * new_size1 + j] = 0;
      }
      else {
        new_data[i * new_size1 + j] = old_data[i * old_size1 + j];
      }
    }
  }

  if (sizeof(char) * old_size1 * old_size2 < sizeof(float) * new_size1 * new_size2) {
    free(pointer);
  }
  return ret_pointer;
}
*/