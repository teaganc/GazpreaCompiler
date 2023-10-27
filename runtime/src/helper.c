#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"

struct Interval {
  int32_t min;
  int32_t max;
};

struct Interval* defaultConstructInterval(int32_t min, int32_t max) {
    struct Interval* ret = malloc (sizeof(struct Interval));
    ret->min = min;
    ret->max = max;
    return ret;
}

struct Interval* copyInterval(struct Interval* interval) {
    struct Interval* ret = malloc (sizeof(struct Interval));
    ret->min = interval->min;
    ret->max = interval->max;
    return ret;
}
/* Tuple Children writing Functions*/

float* createStoreFloat(int8_t* ptr, int32_t index, float value) {
    float* memory = (float*)(((int32_t*)ptr) + (index - 1) );
    *memory = value;
    return memory;
}
int32_t* createStoreInt(int8_t* ptr, int32_t index, int32_t value) {
    int32_t* memory = (int32_t*)(((int32_t*)ptr) + (index - 1));
    *memory = value;
    return memory;
}
bool* createStoreBool(int8_t* ptr, int32_t index, bool value) {
    bool* memory = (bool*)(((int32_t*)ptr) + (index - 1));
    *memory = value;
    return memory;
}
int8_t* createStoreChar(int8_t* ptr, int32_t index, int8_t value) {
    int8_t* memory = (int8_t*)(((int32_t*)ptr) + (index - 1));
    *memory = value;
    return memory;
}
float** createStoreFloatVec(int8_t* ptr, int32_t index, float* value) {
    float** memory = (float**)(((int32_t*)ptr) + (index - 1));
    *memory = value;
    return memory;
}
int32_t** createStoreIntVec(int8_t* ptr, int32_t index, int32_t* value) {
    int32_t** memory = (int32_t**)(((int32_t*)ptr) + (index - 1));
    *memory = value;
    return memory;
}
bool** createStoreBoolVec(int8_t* ptr, int32_t index, bool* value) {
    bool** memory = (bool**)(((int32_t*)ptr) + (index - 1));
    *memory = value;
    return memory;
}
int8_t** createStoreCharVec(int8_t* ptr, int32_t index, int8_t* value) {
    int8_t** memory = (int8_t**)(((int32_t*)ptr) + (index - 1));
    *memory = value;
    return memory;
}
float** createStoreFloatMat(int8_t* ptr, int32_t index, float* value) {
    float** memory = (float**)(((int32_t*)ptr) + (index - 1));
    *memory = value;
    return memory;
}
int32_t** createStoreIntMat(int8_t* ptr, int32_t index, int32_t* value) {
    int32_t** memory = (int32_t**)(((int32_t*)ptr) + (index - 1));
    *memory = value;
    return memory;
}
bool** createStoreBoolMat(int8_t* ptr, int32_t index, bool* value) {
    bool** memory = (bool**)(((int32_t*)ptr) + (index - 1));
    *memory = value;
    return memory;
}
int8_t** createStoreCharMat(int8_t* ptr, int32_t index, int8_t* value) {
    int8_t** memory = (int8_t**)(((int32_t*)ptr) + (index - 1));
    *memory = value;
    return memory;
}

/* Vector and Matrix Inits*/
// no changes to size values as initializing memory space
int32_t* initNoneMat(int32_t size0, int32_t size1) {
    int32_t* ptr = calloc(size0 * size1 + 2, sizeof(int32_t));
    ptr[0] = size0;
    ptr[1] = size1;
    return (int32_t*)ptr;
}
float* initFloatMat(int32_t size0, int32_t size1) {
    int32_t* ptr = calloc(size0 * size1 + 2, sizeof(float));
    ptr[0] = size0;
    ptr[1] = size1;
    return (float*)ptr;
}
int32_t* initIntMat(int32_t size0, int32_t size1) {
    int32_t* ptr = calloc(size0 * size1 + 2, sizeof(int32_t));
    ptr[0] = size0;
    ptr[1] = size1;
    return (int32_t*)ptr;
}
bool* initBoolMat(int32_t size0, int32_t size1) {
    int32_t* ptr = calloc(size0 * size1 + 8, sizeof(bool));
    ptr[0] = size0;
    ptr[1] = size1;
    return (bool*)ptr;
}
int8_t* initCharMat(int32_t size0, int32_t size1) {
    int32_t* ptr = calloc(size0 * size1 + 8, sizeof(int8_t));
    ptr[0] = size0;
    ptr[1] = size1;
    return (int8_t*)ptr;
}
int32_t* initNoneVec(int32_t size) {
    int32_t* ptr = calloc(size + 1, sizeof(int32_t));
    ptr[0] = size;
    return (int32_t*)ptr; 
}
float* initFloatVec(int32_t size) {
    int32_t* ptr = calloc(size + 1, sizeof(float));
    ptr[0] = size;
    return (float*)ptr; 
}
int32_t* initIntVec(int32_t size) {
    int32_t* ptr = calloc(size + 1, sizeof(int32_t));
    ptr[0] = size;
    return (int32_t*)ptr; 
}
bool* initBoolVec(int32_t size) {
    int32_t* ptr = calloc(size + 4, sizeof(bool));
    ptr[0] = size;
    return (bool*)ptr; 
}
int8_t* initCharVec(int32_t size) {
    int32_t* ptr = calloc(size + 4, sizeof(int8_t));
    ptr[0] = size;
    return (int8_t*)ptr; 
}
int8_t* initAndWriteString(int8_t* string, int32_t size) {
    int32_t* ret = malloc(size * sizeof(int8_t) + sizeof(int32_t));
    *ret = size;
    int8_t* data = (int8_t*)(ret+1);
    memcpy(data, string, size);
    return (int8_t*)ret;
}
int32_t* initInterval(struct Interval* interval) {
    int32_t size = interval->max - interval->min + 1;
    int32_t* ptr = calloc(size + 1, sizeof(int32_t));
    ptr[0] = size;
    //free(interval);
    return (int32_t*)ptr; 
}

// init a vector from another vectors size

float* initFloatVecVec(float* vector) {
    int32_t size = *(int32_t*)vector;
    int32_t* ptr = calloc(size + 1, sizeof(float));
    ptr[0] = size;
    return (float*)ptr; 
}
int32_t* initIntVecVec(int32_t* vector) {
    int32_t size = *(int32_t*)vector;
    int32_t* ptr = calloc(size + 1, sizeof(int32_t));
    ptr[0] = size;
    return (int32_t*)ptr; 
}
bool* initBoolVecVec(bool* vector) {
    int32_t size = *(int32_t*)vector;
    int32_t* ptr = calloc(size + 4, sizeof(bool));
    ptr[0] = size;
    return (bool*)ptr; 
}
int8_t* initCharVecVec(int8_t* vector) {
    int32_t size = *(int32_t*)vector;
    int32_t* ptr = calloc(size + 4, sizeof(int8_t));
    ptr[0] = size;
    return (int8_t*)ptr; 
}

// init a matrix from two vectors
int32_t* initIntMatVecVec(int32_t* vector0, int32_t* vector1) {
    int32_t size0 = *(int32_t*)vector0;
    int32_t size1 = *(int32_t*)vector1;
    
    int32_t* ptr = calloc(size0 * size1 + 2, sizeof(int32_t));
    ptr[0] = size0;
    ptr[1] = size1;
    return (int32_t*)ptr;
}
int32_t* initIntMatIntervalVec(struct Interval* interval, int32_t* vector) {
    int32_t size0 = interval->max - interval->min + 1;
    int32_t size1 = *(int32_t*)vector;
    
    int32_t* ptr = calloc(size0 * size1 + 2, sizeof(int32_t));
    ptr[0] = size0;
    ptr[1] = size1;
    //free(interval);
    return (int32_t*)ptr;
}
int32_t* initIntMatVecInterval(int32_t* vector, struct Interval* interval) {
    int32_t size0 = *(int32_t*)vector;
    int32_t size1 = interval->max - interval->min + 1;
    
    int32_t* ptr = calloc(size0 * size1 + 2, sizeof(int32_t));
    ptr[0] = size0;
    ptr[1] = size1;
    //free(interval);
    return (int32_t*)ptr;
}
int32_t* initIntMatIntervalInterval(struct Interval* interval0, struct Interval* interval1) {
    int32_t size0 = interval0->max - interval0->min + 1;
    int32_t size1 = interval1->max - interval1->min + 1;
    
    int32_t* ptr = calloc(size0 * size1 + 2, sizeof(int32_t));
    ptr[0] = size0;
    ptr[1] = size1;

    // TODO: This might leak but i dont think so
    //free(interval0);
    //free(interval1);
    return (int32_t*)ptr;
}
float* initFloatMatVecVec(float* vector0, float* vector1) {
    int32_t size0 = *(int32_t*)vector0;
    int32_t size1 = *(int32_t*)vector1;
    
    int32_t* ptr = calloc(size0 * size1 + 2, sizeof(float));
    ptr[0] = size0;
    ptr[1] = size1;
    return (float*)ptr;
}
bool* initBoolMatVecVec(bool* vector0, bool* vector1) {
    int32_t size0 = *(int32_t*)vector0;
    int32_t size1 = *(int32_t*)vector1;
    
    int32_t* ptr = calloc(size0 * size1 + 8, sizeof(bool));
    ptr[0] = size0;
    ptr[1] = size1;
    return (bool*)ptr;
}
int8_t* initCharMatVecVec(int8_t* vector0, int8_t* vector1) {
    int32_t size0 = *(int32_t*)vector0;
    int32_t size1 = *(int32_t*)vector1;
    
    int32_t* ptr = calloc(size0 * size1 + 8, sizeof(int8_t));
    ptr[0] = size0;
    ptr[1] = size1;
    return (int8_t*)ptr;
}
/* Matrix and Vector Writing functions*/

// writing a value into a matrix
void writeBoolMat(bool value, bool* matrix, int32_t index0, int32_t index1) {
    index0--;
    index1--;
    int32_t size0 = *(int32_t*)matrix;
    int32_t size1 = *(((int32_t*)matrix) + 1);
    matrix = (bool*)(((int32_t*)matrix) + 2);
    if (!(index0 < size0 && index1 < size1)) {
        matrixIndexOutBound(size0, size1, index0, index1);
    }
    matrix[index0 * size1 + index1] = value;
}

void writeFloatMat(float value, float* matrix, int32_t index0, int32_t index1) {
    index0--;
    index1--;
    int32_t size0 = *(int32_t*)matrix;
    int32_t size1 = *(((int32_t*)matrix) + 1);
    matrix = (float*)(((int32_t*)matrix) + 2);
    if (!(index0 < size0 && index1 < size1)) {
        matrixIndexOutBound(size0, size1, index0, index1);
    }
    matrix[index0 * size1 + index1] = value;
}

void writeIntMat(int32_t value, int32_t* matrix, int32_t index0, int32_t index1) {
    index0--;
    index1--;
    int32_t size0 = *(int32_t*)matrix;
    int32_t size1 = *(((int32_t*)matrix) + 1);
    matrix = (int32_t*)(((int32_t*)matrix) + 2);

    if (!(index0 < size0 && index1 < size1)) {
        matrixIndexOutBound(size0, size1, index0, index1);
    }

    matrix[index0 * size1 + index1] = value;
}

void writeCharMat(int8_t value, int8_t* matrix, int32_t index0, int32_t index1) {
    index0--;
    index1--;
    int32_t size0 = *(int32_t*)matrix;
    int32_t size1 = *(((int32_t*)matrix) + 1);
    matrix = (int8_t*)(((int32_t*)matrix) + 2);
    if (!(index0 < size0 && index1 < size1)) {
        matrixIndexOutBound(size0, size1, index0, index1);
    }
    matrix[index0 * size1 + index1] = value;
}

// writing a vector of values into a matrix literal
void writeBoolMatVec(bool* vector, bool* matrix, int32_t index) {
    index--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix) + 1);
    matrix = (bool*)(((int32_t*)matrix) + 2);

    int32_t vector_size = *(int32_t*)vector;
    bool* vector_data = (bool*)(((int32_t*)vector) + 1);

    if (vector_size > matrix_size1) {
        vectorMatrixMismatchError(vector_size, matrix_size1);
    }

    matrix = matrix + index * matrix_size1;
    memcpy(matrix, vector_data, vector_size * sizeof(bool));
    free(vector);
}
void writeFloatMatVec(float* vector, float* matrix, int32_t index) {
    index--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix) + 1);
    matrix = (float*)(((int32_t*)matrix) + 2);

    int32_t vector_size = *(int32_t*)vector;
    float* vector_data = (float*)(((int32_t*)vector) + 1);

    if (vector_size > matrix_size1) {
        vectorMatrixMismatchError(vector_size, matrix_size1);
    }

    matrix = matrix + index * matrix_size1;
    memcpy(matrix, vector_data, vector_size * sizeof(float));
    free(vector);
}
void writeIntMatVec(int32_t* vector, int32_t* matrix, int32_t index) {
    index--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix) + 1);
    matrix = (int32_t*)(((int32_t*)matrix) + 2);

    int32_t vector_size = *(int32_t*)vector;
    int32_t* vector_data = (int32_t*)(((int32_t*)vector) + 1);

    if (vector_size > matrix_size1) {
        vectorMatrixMismatchError(vector_size, matrix_size1);
    }

    matrix = matrix + index * matrix_size1;
    memcpy(matrix, vector_data, vector_size * sizeof(int32_t));
    free(vector);
}

void writeCharMatVec(int8_t* vector, int8_t* matrix, int32_t index) {
    index--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix) + 1);
    matrix = (int8_t*)(((int32_t*)matrix) + 2);

    int32_t vector_size = *(int32_t*)vector;
    int8_t* vector_data = (int8_t*)(((int32_t*)vector) + 1);

    if (vector_size > matrix_size1) {
        vectorMatrixMismatchError(vector_size, matrix_size1);
    }

    matrix = matrix + index * matrix_size1;
    memcpy(matrix, vector_data, vector_size * sizeof(int8_t));
    free(vector);
}

// write a value into a vector
void writeBoolVec(bool value, bool* vector, int32_t index) {
    index--;
    int32_t size = *(int32_t*)vector;
    vector = (bool*)(((int32_t*)vector) + 1);
    if (index >= size) {
        vectorIndexOutBound(size, index);
    }
    vector[index] = value; 
}

void writeFloatVec(float value, float* vector, int32_t index) {
    index--;
    int32_t size = *(int32_t*)vector;
    vector = (float*)(((int32_t*)vector) + 1);
    if (index >= size) {
        vectorIndexOutBound(size, index);
    }
    vector[index] = value; 
}

void writeIntVec(int32_t value, int32_t* vector, int32_t index) {
    index--;
    int32_t size = *(int32_t*)vector;
    vector = (int32_t*)(((int32_t*)vector) + 1);
    if (index >= size) {
        vectorIndexOutBound(size, index);
    }
    vector[index] = value; 
}

void writeCharVec(int8_t value, int8_t* vector, int32_t index) {
    index--;
    int32_t size = *(int32_t*)vector;
    vector = (int8_t*)(((int32_t*)vector) + 1);
    if (index >= size) {
        vectorIndexOutBound(size, index);
    }
    vector[index] = value; 
}

/* Variable Reference of Vectors/Matrixes*/

float* copyFloatMat(float* pointer) {
    int32_t size0 = *(int32_t*)pointer;
    int32_t size1 = *(((int32_t*)pointer) + 1);
    float* ret = malloc(sizeof(float) * (size0 * size1 + 2));
    memcpy(ret, pointer, sizeof(float) * (size0 * size1 + 2));
    return ret;
}
int32_t* copyIntMat(int32_t* pointer) {
    int32_t size0 = *(int32_t*)pointer;
    int32_t size1 = *(((int32_t*)pointer) + 1);
    int32_t* ret = malloc(sizeof(int32_t) * (size0 * size1 + 2));
    memcpy(ret, pointer, sizeof(int32_t) * (size0 * size1 + 2));
    return ret;
}
bool* copyBoolMat(bool* pointer) {
    int32_t size0 = *(int32_t*)pointer;
    int32_t size1 = *(((int32_t*)pointer) + 1);
    bool* ret = malloc(sizeof(bool) * (size0 * size1 + 8));
    memcpy(ret, pointer, sizeof(bool) * (size0 * size1 + 8));
    return ret;
}
int8_t* copyCharMat(int8_t* pointer) {
    int32_t size0 = *(int32_t*)pointer;
    int32_t size1 = *(((int32_t*)pointer) + 1);
    int8_t* ret = malloc(sizeof(int8_t) * (size0 * size1 + 8));
    memcpy(ret, pointer, sizeof(int8_t) * (size0 * size1 + 8));
    return ret;
}
float* copyFloatVec(float* pointer) {
    int32_t size = *(int32_t*)pointer;
    float* ret = malloc(sizeof(float) * (size + 1));
    memcpy(ret, pointer, sizeof(float) * (size + 1));
    return ret;
}
int32_t* copyIntVec(int32_t* pointer) {
    int32_t size = *(int32_t*)pointer;
    int32_t* ret = malloc(sizeof(int32_t) * (size + 1));
    memcpy(ret, pointer, sizeof(int32_t) * (size + 1));
    return ret;
}
bool* copyBoolVec(bool* pointer) {
    int32_t size = *(int32_t*)pointer;
    bool* ret = malloc(sizeof(bool) * (size + 4));
    memcpy(ret, pointer, sizeof(bool) * (size + 4));
    return ret;
}
int8_t* copyCharVec(int8_t* pointer) {
    int32_t size = *(int32_t*)pointer;
    int8_t* ret = malloc(sizeof(int8_t) * (size + 4));
    memcpy(ret, pointer, sizeof(int8_t) * (size + 4));
    return ret;
}

// returning scalars from indexing
float getFloatVec(float* vector, int32_t index) {
    index--;
    int32_t size = *(int32_t*)vector;
    if (index >= size) {
        vectorIndexOutBound(size, index+1);
    }
    float* data = (float*)(((int32_t*)vector) + 1);
    return data[index];
}
int32_t getIntVec(int32_t* vector, int32_t index) {
    index--;
    int32_t size = *(int32_t*)vector;
    if (index >= size) {
        vectorIndexOutBound(size, index+1);
    }
    int32_t* data = (int32_t*)(((int32_t*)vector) + 1);
    return data[index];
}
bool getBoolVec(bool* vector, int32_t index) {
    index--;
    int32_t size = *(int32_t*)vector;
    if (index >= size) {
        vectorIndexOutBound(size, index+1);
    }
    bool* data = (bool*)(((int32_t*)vector) + 1);
    return data[index];
}
int8_t getCharVec(int8_t* vector, int32_t index) {
    index--;
    int32_t size = *(int32_t*)vector;
    if (index >= size) {
        vectorIndexOutBound(size, index+1);
    }
    int8_t* data = (int8_t*)(((int32_t*)vector) + 1);
    return data[index];
}
int32_t getInterval(struct Interval* interval, int32_t index) {
    index--;
    int32_t size = interval->max - interval->min + 1;
    if (index >= size) {
        vectorIndexOutBound(size, index+1);
    }
    int32_t ret = interval->min + index;
    // TODO: this might leak but I dont think so
    return ret;
}
float getFloatMat(float* matrix, int32_t index0, int32_t index1) {
    index0--;
    index1--;
    int32_t size0 = *((int32_t*)matrix);
    int32_t size1 = *(((int32_t*)matrix) + 1);
    if (index0 >= size0 || index1 >= size1) {
        matrixIndexOutBound(size0, size1, index0+1, index1+1);
    }
    float* data = (float*)(((int32_t*)matrix) + 2);
    return data[index0 * size1 + index1];
}
int32_t getIntMat(int32_t* matrix, int32_t index0, int32_t index1) {
    index0--;
    index1--;
    int32_t size0 = *((int32_t*)matrix);
    int32_t size1 = *(((int32_t*)matrix) + 1);
    if (index0 >= size0 || index1 >= size1) {
        matrixIndexOutBound(size0, size1, index0+1, index1+1);
    }
    int32_t* data = (int32_t*)(((int32_t*)matrix) + 2);
    return data[index0 * size1 + index1];
}
bool getBoolMat(bool* matrix, int32_t index0, int32_t index1) {
    index0--;
    index1--;
    int32_t size0 = *((int32_t*)matrix);
    int32_t size1 = *(((int32_t*)matrix) + 1);
    if (index0 >= size0 || index1 >= size1) {
        matrixIndexOutBound(size0, size1, index0+1, index1+1);
    }
    bool* data = (bool*)(((int32_t*)matrix) + 2);
    return data[index0 * size1 + index1];
}
int8_t getCharMat(int8_t* matrix, int32_t index0, int32_t index1) {
    index0--;
    index1--;
    int32_t size0 = *((int32_t*)matrix);
    int32_t size1 = *(((int32_t*)matrix) + 1);
    if (index0 >= size0 || index1 >= size1) {
        matrixIndexOutBound(size0, size1, index0+1, index1+1);
    }

    int8_t* data = (int8_t*)(((int32_t*)matrix) + 2);
    return data[index0 * size1 + index1];
}

// get vector from indexing vectors
float* getFloatVecIntVec(float* vector, int32_t* index) {
    int32_t vector_size = *(int32_t*)vector;
    float* vector_data = (float*)(((int32_t*)vector) + 1);

    int32_t index_size = *(int32_t*)index;
    int32_t* index_data = (int32_t*)(((int32_t*)index) + 1);

    int32_t* ret = malloc(sizeof(float) * (index_size) + sizeof(int32_t));
    float* ret_data = (float*)(ret + 1);
    *ret = index_size;
    
    for (size_t i = 0 ; i < index_size; i++) {
        int32_t j = index_data[i] - 1;
        if (j >= vector_size) {
            vectorIndexOutBound(vector_size, j);
        }
        ret_data[i] = vector_data[j];
    }
    //free(index);
    return (float*)ret;
}
int32_t* getIntVecIntVec(int32_t* vector, int32_t* index) {
    int32_t vector_size = *(int32_t*)vector;
    int32_t* vector_data = (int32_t*)(((int32_t*)vector) + 1);

    int32_t index_size = *(int32_t*)index;
    int32_t* index_data = (int32_t*)(((int32_t*)index) + 1);

    int32_t* ret = malloc(sizeof(int32_t) * (index_size) + sizeof(int32_t));
    int32_t* ret_data = (int32_t*)(ret + 1);
    *ret = index_size;
    
    for (size_t i = 0 ; i < index_size; i++) {
        int32_t j = index_data[i] - 1;
        if (j >= vector_size) {
            vectorIndexOutBound(vector_size, j);
        }
        ret_data[i] = vector_data[j];
    }
    //free(index);
    return (int32_t*)ret;
}
bool* getBoolVecIntVec(bool* vector, int32_t* index) {
    int32_t vector_size = *(int32_t*)vector;
    bool* vector_data = (bool*)(((int32_t*)vector) + 1);

    int32_t index_size = *(int32_t*)index;
    int32_t* index_data = (int32_t*)(((int32_t*)index) + 1);

    int32_t* ret = malloc(sizeof(bool) * (index_size) + sizeof(int32_t));
    bool* ret_data = (bool*)(ret + 1);
    *ret = index_size;
    
    for (size_t i = 0 ; i < index_size; i++) {
        int32_t j = index_data[i] - 1;
        if (j >= vector_size) {
            vectorIndexOutBound(vector_size, j);
        }
        ret_data[i] = vector_data[j];
    }
    //free(index);
    return (bool*)ret;
}
int8_t* getCharVecIntVec(int8_t* vector, int32_t* index) {
    int32_t vector_size = *(int32_t*)vector;
    int8_t* vector_data = (int8_t*)(((int32_t*)vector) + 1);

    int32_t index_size = *(int32_t*)index;
    int32_t* index_data = (int32_t*)(((int32_t*)index) + 1);

    int32_t* ret = malloc(sizeof(int8_t) * (index_size) + sizeof(int32_t));
    int8_t* ret_data = (int8_t*)(ret + 1);
    *ret = index_size;
    
    for (size_t i = 0 ; i < index_size; i++) {
        int32_t j = index_data[i] - 1;
        if (j >= vector_size) {
            vectorIndexOutBound(vector_size, j);
        }
        ret_data[i] = vector_data[j];
    }
    //free(index);
    return (int8_t*)ret;
}
float* getFloatVecInterval(float* vector, struct Interval* index) {
    int32_t vector_size = *(int32_t*)vector;
    float* vector_data = (float*)(((int32_t*)vector) + 1);

    int32_t index_size = index->max - index->min + 1;

    int32_t* ret = malloc(sizeof(float) * (index_size) + sizeof(int32_t));
    float* ret_data = (float*)(ret + 1);
    *ret = index_size;
    
    for (size_t i = 0 ; i < index_size; i++) {
        int32_t j = index->min + i - 1;
        if (j >= vector_size) {
            vectorIndexOutBound(vector_size, j);
        }
        ret_data[i] = vector_data[j];
    }

    //free(index);
    return (float*)ret;
}
int32_t* getIntVecInterval(int32_t* vector, struct Interval* index) {
    int32_t vector_size = *(int32_t*)vector;
    int32_t* vector_data = (int32_t*)(((int32_t*)vector) + 1);

    int32_t index_size = index->max - index->min + 1;

    int32_t* ret = malloc(sizeof(int32_t) * (index_size) + sizeof(int32_t));
    int32_t* ret_data = (int32_t*)(ret + 1);
    *ret = index_size;
    
    for (size_t i = 0 ; i < index_size; i++) {
        int32_t j = index->min + i - 1;
        if (j >= vector_size) {
            vectorIndexOutBound(vector_size, j);
        }
        ret_data[i] = vector_data[j];
    }

    //free(index);
    return (int32_t*)ret;
}
bool* getBoolVecInterval(bool* vector, struct Interval* index) {
    int32_t vector_size = *(int32_t*)vector;
    bool* vector_data = (bool*)(((int32_t*)vector) + 1);

    int32_t index_size = index->max - index->min + 1;

    int32_t* ret = malloc(sizeof(bool) * (index_size) + sizeof(int32_t));
    bool* ret_data = (bool*)(ret + 1);
    *ret = index_size;
    
    for (size_t i = 0 ; i < index_size; i++) {
        int32_t j = index->min + i - 1;
        if (j >= vector_size) {
            vectorIndexOutBound(vector_size, j);
        }
        ret_data[i] = vector_data[j];
    }

    //free(index);
    return (bool*)ret;
}

int8_t* getCharVecInterval(int8_t* vector, struct Interval* index) {
    int32_t vector_size = *(int32_t*)vector;
    int8_t* vector_data = (int8_t*)(((int32_t*)vector) + 1);

    int32_t index_size = index->max - index->min + 1;

    int32_t* ret = malloc(sizeof(int8_t) * (index_size) + sizeof(int32_t));
    int8_t* ret_data = (int8_t*)(ret + 1);
    *ret = index_size;
    
    for (size_t i = 0 ; i < index_size; i++) {
        int32_t j = index->min + i - 1;
        if (j >= vector_size) {
            vectorIndexOutBound(vector_size, j);
        }
        ret_data[i] = vector_data[j];
    }

    //free(index);
    return (int8_t*)ret;
}
 // Matrix indexing with non scalars and scalars

float* getFloatMatIntIntVec(float* matrix, int32_t index0, int32_t* index1) {
    index0--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    float* matrix_data = (float*)(((int32_t*)matrix) + 2);

    int32_t index1_size = *(int32_t*)index1;
    float* index1_data = (float*)(((int32_t*)index1) + 1);

    int32_t* ret = malloc(sizeof(float) * (index1_size) + sizeof(int32_t));
    float* ret_data = (float*)(ret + 1);
    *ret = index1_size;
    
    for (size_t i = 0 ; i < index1_size; i++) {
        int32_t j = index1_data[i] - 1;
        if (index0 >= matrix_size0 || j >= matrix_size1) {
            matrixIndexOutBound(matrix_size0, matrix_size1, index0, j);
        }
        ret_data[i] = matrix_data[index0 * matrix_size1 + j];
    }
    //free(index1);
    return (float*)ret;
}
float* getFloatMatIntInterval(float* matrix, int32_t index0, struct Interval* index1) {
    index0--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    float* matrix_data = (float*)(((int32_t*)matrix) + 2);

    int32_t index1_size = index1->max - index1->min + 1;

    int32_t* ret = malloc(sizeof(float) * (index1_size) + sizeof(int32_t));
    float* ret_data = (float*)(ret + 1);
    *ret = index1_size;
    
    for (size_t i = 0 ; i < index1_size; i++) {
        int32_t j = index1->min + i - 1;
        if (index0 >= matrix_size0 || j >= matrix_size1) {
            matrixIndexOutBound(matrix_size0, matrix_size1, index0, j);
        }
        ret_data[i] = matrix_data[index0 * matrix_size1 + j];
    }

    //free(index1);
    return (float*)ret;
}
float* getFloatMatIntVecInt(float* matrix, int32_t* index0, int32_t index1) {
    index1--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    float* matrix_data = (float*)(((int32_t*)matrix) + 2);

    int32_t index0_size = *(int32_t*)index0;
    float* index0_data = (float*)(((int32_t*)index0) + 1);

    int32_t* ret = malloc(sizeof(float) * (index0_size) + sizeof(int32_t));
    float* ret_data = (float*)(ret + 1);
    *ret = index0_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        int32_t j = index0_data[i] - 1;
        if (j >= matrix_size0 || index1 >= matrix_size1) {
            matrixIndexOutBound(matrix_size0, matrix_size1, j, index1);
        }
        ret_data[i] = matrix_data[j * matrix_size1 + index1];
    }
    //free(index0);
    return (float*)ret;
}
float* getFloatMatIntervalInt(float* matrix, struct Interval* index0, int32_t index1) {
    index1--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    float* matrix_data = (float*)(((int32_t*)matrix) + 2);

    int32_t index0_size = index0->max - index0->min + 1;

    int32_t* ret = malloc(sizeof(float) * (index0_size) + sizeof(int32_t));
    float* ret_data = (float*)(ret + 1);
    *ret = index0_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        int32_t j = index0->min + i - 1;
        if (j >= matrix_size0 || index1 >= matrix_size1) {
            matrixIndexOutBound(matrix_size0, matrix_size1, j, index1);
        }
        ret_data[i] = matrix_data[j * matrix_size1 + index1];
    }

    //free(index0);
    return (float*)ret;
}
float* getFloatMatIntervalInterval(float* matrix, struct Interval* index0, struct Interval* index1) {
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    float* matrix_data = (float*)(((int32_t*)matrix) + 2);

    int32_t index0_size = index0->max - index0->min + 1;
    int32_t index1_size = index1->max - index1->min + 1;

    int32_t* ret = malloc(sizeof(float) * (index0_size) * (index1_size) + sizeof(int32_t));
    float* ret_data = (float*)(ret + 2);
    *ret = index0_size;
    *(ret + 1) =  index1_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        for (size_t j = 0 ; j < index1_size; j++) {
            int32_t k = index0->min + i - 1;
            int32_t l = index1->min + j - 1;
            if (k >= matrix_size0 || l >= matrix_size1) {
                matrixIndexOutBound(matrix_size0, matrix_size1, k, l);
            }
            ret_data[k * index1_size + l] = matrix_data[k * matrix_size1 + l];
        }
    }

    //free(index0);
    //free(index1);
    return (float*)ret;
}
float* getFloatMatIntVecIntVec(float* matrix, int32_t* index0, int32_t* index1) {
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    float* matrix_data = (float*)(((int32_t*)matrix) + 2);

    int32_t index0_size = *(int32_t*)index0;
    float* index0_data = (float*)(((int32_t*)index0) + 1);
    int32_t index1_size = *(int32_t*)index1;
    float* index1_data = (float*)(((int32_t*)index1) + 1);

    int32_t* ret = malloc(sizeof(float) * (index0_size) * (index1_size) + sizeof(int32_t));
    float* ret_data = (float*)(ret + 2);
    *ret = index0_size;
    *(ret + 1) =  index1_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        for (size_t j = 0 ; j < index1_size; j++) {
            int32_t k = index0_data[i] - 1;
            int32_t l = index1_data[j] - 1;
            if (k >= matrix_size0 || l >= matrix_size1) {
                matrixIndexOutBound(matrix_size0, matrix_size1, k, l);
            }
            ret_data[k * index1_size + l] = matrix_data[k * matrix_size1 + l];
        }
    }

    return (float*)ret;
}

float* getFloatMatIntervalIntVec(float* matrix, struct Interval* index0, int32_t* index1) {
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    float* matrix_data = (float*)(((int32_t*)matrix) + 2);

    int32_t index0_size = index0->max - index0->min + 1;
    int32_t index1_size = *(int32_t*)index1;
    float* index1_data = (float*)(((int32_t*)index1) + 1);

    int32_t* ret = malloc(sizeof(float) * (index0_size) * (index1_size) + sizeof(int32_t));
    float* ret_data = (float*)(ret + 2);
    *ret = index0_size;
    *(ret + 1) =  index1_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        for (size_t j = 0 ; j < index1_size; j++) {
            int32_t k = index0->min + i - 1;
            int32_t l = index1_data[j] - 1;
            if (k >= matrix_size0 || l >= matrix_size1) {
                matrixIndexOutBound(matrix_size0, matrix_size1, k, l);
            }
            ret_data[k * index1_size + l] = matrix_data[k * matrix_size1 + l];
        }
    }

    //free(index0);
   return (float*)ret;
}

float* getFloatMatIntVecInterval(float* matrix, int32_t* index0, struct Interval* index1) {
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    float* matrix_data = (float*)(((int32_t*)matrix) + 2);

    int32_t index0_size = *(int32_t*)index0;
    float* index0_data = (float*)(((int32_t*)index0) + 1);
    int32_t index1_size = index1->max - index1->min + 1;

    int32_t* ret = malloc(sizeof(float) * (index0_size) * (index1_size) + sizeof(int32_t));
    float* ret_data = (float*)(ret + 2);
    *ret = index0_size;
    *(ret + 1) =  index1_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        for (size_t j = 0 ; j < index1_size; j++) {
            int32_t k = index0_data[i] - 1;
            int32_t l = index1->min + j - 1;
            if (k >= matrix_size0 || l >= matrix_size1) {
                matrixIndexOutBound(matrix_size0, matrix_size1, k, l);
            }
            ret_data[k * index1_size + l] = matrix_data[k * matrix_size1 + l];
        }
    }

    //free(index1);
    return (float*)ret;
}

 // Int Mat indexing with non scalar scalar

int32_t* getIntMatIntIntVec(int32_t* matrix, int32_t index0, int32_t* index1) {
    index0--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    int32_t* matrix_data = (int32_t*)(((int32_t*)matrix) + 2);

    int32_t index1_size = *(int32_t*)index1;
    int32_t* index1_data = (int32_t*)(((int32_t*)index1) + 1);

    int32_t* ret = malloc(sizeof(int32_t) * (index1_size) + sizeof(int32_t));
    int32_t* ret_data = (int32_t*)(ret + 1);
    *ret = index1_size;
    
    for (size_t i = 0 ; i < index1_size; i++) {
        int32_t j = index1_data[i] - 1;
        if (index0 >= matrix_size0 || j >= matrix_size1) {
            matrixIndexOutBound(matrix_size0, matrix_size1, index0, j);
        }
        ret_data[i] = matrix_data[index0 * matrix_size1 + j];
    }
    //free(index1);
    return (int32_t*)ret;
}
int32_t* getIntMatIntInterval(int32_t* matrix, int32_t index0, struct Interval* index1) {
    index0--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    int32_t* matrix_data = (int32_t*)(((int32_t*)matrix) + 2);

    int32_t index1_size = index1->max - index1->min + 1;

    int32_t* ret = malloc(sizeof(int32_t) * (index1_size) + sizeof(int32_t));
    int32_t* ret_data = (int32_t*)(ret + 1);
    *ret = index1_size;
    
    for (size_t i = 0 ; i < index1_size; i++) {
        int32_t j = index1->min + i - 1;
        if (index0 >= matrix_size0 || j >= matrix_size1) {
            matrixIndexOutBound(matrix_size0, matrix_size1, index0, j);
        }
        ret_data[i] = matrix_data[index0 * matrix_size1 + j];
    }

    //free(index1);
    return (int32_t*)ret;
}

int32_t* getIntMatIntVecInt(int32_t* matrix, int32_t* index0, int32_t index1) {
    index1--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    int32_t* matrix_data = (int32_t*)(((int32_t*)matrix) + 2);

    int32_t index0_size = *(int32_t*)index0;
    int32_t* index0_data = (int32_t*)(((int32_t*)index0) + 1);

    int32_t* ret = malloc(sizeof(int32_t) * (index0_size) + sizeof(int32_t));
    int32_t* ret_data = (int32_t*)(ret + 1);
    *ret = index0_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        int32_t j = index0_data[i] - 1;
        if (j >= matrix_size0 || index1 >= matrix_size1) {
            matrixIndexOutBound(matrix_size0, matrix_size1, j, index1);
        }
        ret_data[i] = matrix_data[j * matrix_size1 + index1];
    }
    //free(index0);
    return (int32_t*)ret;
}
int32_t* getIntMatIntervalInt(int32_t* matrix, struct Interval* index0, int32_t index1) {
    index1--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    int32_t* matrix_data = (int32_t*)(((int32_t*)matrix) + 2);

    int32_t index0_size = index0->max - index0->min + 1;

    int32_t* ret = malloc(sizeof(int32_t) * (index0_size) + sizeof(int32_t));
    int32_t* ret_data = (int32_t*)(ret + 1);
    *ret = index0_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        int32_t j = index0->min + i - 1;
        if (j >= matrix_size0 || index1 >= matrix_size1) {
            matrixIndexOutBound(matrix_size0, matrix_size1, j, index1);
        }
        ret_data[i] = matrix_data[j * matrix_size1 + index1];
    }

    //free(index0);
    return (int32_t*)ret;
}
int32_t* getIntMatIntervalInterval(int32_t* matrix, struct Interval* index0, struct Interval* index1) {
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    int32_t* matrix_data = (int32_t*)(((int32_t*)matrix) + 2);

    int32_t index0_size = index0->max - index0->min + 1;
    int32_t index1_size = index1->max - index1->min + 1;

    int32_t* ret = malloc(sizeof(int32_t) * (index0_size) * (index1_size) + sizeof(int32_t));
    int32_t* ret_data = (int32_t*)(ret + 2);
    *ret = index0_size;
    *(ret + 1) =  index1_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        for (size_t j = 0 ; j < index1_size; j++) {
            int32_t k = index0->min + i - 1;
            int32_t l = index1->min + j - 1;
            if (k >= matrix_size0 || l >= matrix_size1) {
                matrixIndexOutBound(matrix_size0, matrix_size1, k, l);
            }
            ret_data[k * index1_size + l] = matrix_data[k * matrix_size1 + l];
        }
    }

    //free(index0);
    //free(index1);
    return (int32_t*)ret;
}
int32_t* getIntMatIntVecIntVec(int32_t* matrix, int32_t* index0, int32_t* index1) {
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    int32_t* matrix_data = (int32_t*)(((int32_t*)matrix) + 2);

    int32_t index0_size = *(int32_t*)index0;
    int32_t* index0_data = (int32_t*)(((int32_t*)index0) + 1);
    int32_t index1_size = *(int32_t*)index1;
    int32_t* index1_data = (int32_t*)(((int32_t*)index1) + 1);

    int32_t* ret = malloc(sizeof(int32_t) * (index0_size) * (index1_size) + sizeof(int32_t));
    int32_t* ret_data = (int32_t*)(ret + 2);
    *ret = index0_size;
    *(ret + 1) =  index1_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        for (size_t j = 0 ; j < index1_size; j++) {
            int32_t k = index0_data[i] - 1;
            int32_t l = index1_data[j] - 1;
            if (k >= matrix_size0 || l >= matrix_size1) {
                matrixIndexOutBound(matrix_size0, matrix_size1, k, l);
            }
            ret_data[k * index1_size + l] = matrix_data[k * matrix_size1 + l];
        }
    }

    return (int32_t*)ret;
}

int32_t* getIntMatIntervalIntVec(int32_t* matrix, struct Interval* index0, int32_t* index1) {
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    int32_t* matrix_data = (int32_t*)(((int32_t*)matrix) + 2);

    int32_t index0_size = index0->max - index0->min + 1;
    int32_t index1_size = *(int32_t*)index1;
    int32_t* index1_data = (int32_t*)(((int32_t*)index1) + 1);

    int32_t* ret = malloc(sizeof(int32_t) * (index0_size) * (index1_size) + sizeof(int32_t));
    int32_t* ret_data = (int32_t*)(ret + 2);
    *ret = index0_size;
    *(ret + 1) =  index1_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        for (size_t j = 0 ; j < index1_size; j++) {
            int32_t k = index0->min + i - 1;
            int32_t l = index1_data[j] - 1;
            if (k >= matrix_size0 || l >= matrix_size1) {
                matrixIndexOutBound(matrix_size0, matrix_size1, k, l);
            }
            ret_data[k * index1_size + l] = matrix_data[k * matrix_size1 + l];
        }
    }

    //free(index0);
    return (int32_t*)ret;
}
int32_t* getIntMatIntVecInterval(int32_t* matrix, int32_t* index0, struct Interval* index1) {
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    int32_t* matrix_data = (int32_t*)(((int32_t*)matrix) + 2);

    int32_t index0_size = *(int32_t*)index0;
    int32_t* index0_data = (int32_t*)(((int32_t*)index0) + 1);
    int32_t index1_size = index1->max - index1->min + 1;

    int32_t* ret = malloc(sizeof(int32_t) * (index0_size) * (index1_size) + sizeof(int32_t));
    int32_t* ret_data = (int32_t*)(ret + 2);
    *ret = index0_size;
    *(ret + 1) =  index1_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        for (size_t j = 0 ; j < index1_size; j++) {
            int32_t k = index0_data[i] - 1;
            int32_t l = index1->min + j - 1;
            if (k >= matrix_size0 || l >= matrix_size1) {
                matrixIndexOutBound(matrix_size0, matrix_size1, k, l);
            }
            ret_data[k * index1_size + l] = matrix_data[k * matrix_size1 + l];
        }
    }

    //free(index1);
    return (int32_t*)ret;
}

bool* getBoolMatIntIntVec(bool* matrix, int32_t index0, int32_t* index1) {
    index0--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    bool* matrix_data = (bool*)(((int32_t*)matrix) + 2);

    int32_t index1_size = *(int32_t*)index1;
    bool* index1_data = (bool*)(((int32_t*)index1) + 1);

    int32_t* ret = malloc(sizeof(bool) * (index1_size) + sizeof(int32_t));
    bool* ret_data = (bool*)(ret + 1);
    *ret = index1_size;
    
    for (size_t i = 0 ; i < index1_size; i++) {
        int32_t j = index1_data[i] - 1;
        if (index0 >= matrix_size0 || j >= matrix_size1) {
            matrixIndexOutBound(matrix_size0, matrix_size1, index0, j);
        }
        ret_data[i] = matrix_data[index0 * matrix_size1 + j];
    }
    //free(index1);
    return (bool*)ret;
}
bool* getBoolMatIntInterval(bool* matrix, int32_t index0, struct Interval* index1) {
    index0--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    bool* matrix_data = (bool*)(((int32_t*)matrix) + 2);

    int32_t index1_size = index1->max - index1->min + 1;

    int32_t* ret = malloc(sizeof(bool) * (index1_size) + sizeof(int32_t));
    bool* ret_data = (bool*)(ret + 1);
    *ret = index1_size;
    
    for (size_t i = 0 ; i < index1_size; i++) {
        int32_t j = index1->min + i - 1;
        if (index0 >= matrix_size0 || j >= matrix_size1) {
            matrixIndexOutBound(matrix_size0, matrix_size1, index0, j);
        }
        ret_data[i] = matrix_data[index0 * matrix_size1 + j];
    }

    //free(index1);
    return (bool*)ret;
}
bool* getBoolMatIntVecInt(bool* matrix, int32_t* index0, int32_t index1) {
    index1--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    bool* matrix_data = (bool*)(((int32_t*)matrix) + 2);

    int32_t index0_size = *(int32_t*)index0;
    bool* index0_data = (bool*)(((int32_t*)index0) + 1);

    int32_t* ret = malloc(sizeof(bool) * (index0_size) + sizeof(int32_t));
    bool* ret_data = (bool*)(ret + 1);
    *ret = index0_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        int32_t j = index0_data[i] - 1;
        if (j >= matrix_size0 || index1 >= matrix_size1) {
            matrixIndexOutBound(matrix_size0, matrix_size1, j, index1);
        }
        ret_data[i] = matrix_data[j * matrix_size1 + index1];
    }
    //free(index0);
    return (bool*)ret;
}
bool* getBoolMatIntervalInt(bool* matrix, struct Interval* index0, int32_t index1) {
    index1--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    bool* matrix_data = (bool*)(((int32_t*)matrix) + 2);

    int32_t index0_size = index0->max - index0->min + 1;

    int32_t* ret = malloc(sizeof(bool) * (index0_size) + sizeof(int32_t));
    bool* ret_data = (bool*)(ret + 1);
    *ret = index0_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        int32_t j = index0->min + i - 1;
        if (j >= matrix_size0 || index1 >= matrix_size1) {
            matrixIndexOutBound(matrix_size0, matrix_size1, j, index1);
        }
        ret_data[i] = matrix_data[j * matrix_size1 + index1];
    }

    //free(index0);
    return (bool*)ret;
}
bool* getBoolMatIntervalInterval(bool* matrix, struct Interval* index0, struct Interval* index1) {
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    bool* matrix_data = (bool*)(((int32_t*)matrix) + 2);

    int32_t index0_size = index0->max - index0->min + 1;
    int32_t index1_size = index1->max - index1->min + 1;

    int32_t* ret = malloc(sizeof(bool) * (index0_size) * (index1_size) + sizeof(int32_t));
    bool* ret_data = (bool*)(ret + 2);
    *ret = index0_size;
    *(ret + 1) =  index1_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        for (size_t j = 0 ; j < index1_size; j++) {
            int32_t k = index0->min + i - 1;
            int32_t l = index1->min + j - 1;
            if (k >= matrix_size0 || l >= matrix_size1) {
                matrixIndexOutBound(matrix_size0, matrix_size1, k, l);
            }
            ret_data[k * index1_size + l] = matrix_data[k * matrix_size1 + l];
        }
    }

    //free(index0);
    //free(index1);
    return (bool*)ret;
}

bool* getBoolMatIntVecIntVec(bool* matrix, int32_t* index0, int32_t* index1) {
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    bool* matrix_data = (bool*)(((int32_t*)matrix) + 2);

    int32_t index0_size = *(int32_t*)index0;
    bool* index0_data = (bool*)(((int32_t*)index0) + 1);
    int32_t index1_size = *(int32_t*)index1;
    bool* index1_data = (bool*)(((int32_t*)index1) + 1);

    int32_t* ret = malloc(sizeof(bool) * (index0_size) * (index1_size) + sizeof(int32_t));
    bool* ret_data = (bool*)(ret + 2);
    *ret = index0_size;
    *(ret + 1) =  index1_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        for (size_t j = 0 ; j < index1_size; j++) {
            int32_t k = index0_data[i] - 1;
            int32_t l = index1_data[j] - 1;
            if (k >= matrix_size0 || l >= matrix_size1) {
                matrixIndexOutBound(matrix_size0, matrix_size1, k, l);
            }
            ret_data[k * index1_size + l] = matrix_data[k * matrix_size1 + l];
        }
    }

    return (bool*)ret;
}

bool* getBoolMatIntervalIntVec(bool* matrix, struct Interval* index0, int32_t* index1) {
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    bool* matrix_data = (bool*)(((int32_t*)matrix) + 2);

    int32_t index0_size = index0->max - index0->min + 1;
    int32_t index1_size = *(int32_t*)index1;
    bool* index1_data = (bool*)(((int32_t*)index1) + 1);

    int32_t* ret = malloc(sizeof(bool) * (index0_size) * (index1_size) + sizeof(int32_t));
    bool* ret_data = (bool*)(ret + 2);
    *ret = index0_size;
    *(ret + 1) =  index1_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        for (size_t j = 0 ; j < index1_size; j++) {
            int32_t k = index0->min + i - 1;
            int32_t l = index1_data[j] - 1;
            if (k >= matrix_size0 || l >= matrix_size1) {
                matrixIndexOutBound(matrix_size0, matrix_size1, k, l);
            }
            ret_data[k * index1_size + l] = matrix_data[k * matrix_size1 + l];
        }
    }

    //free(index0);
    return (bool*)ret;
}
bool* getBoolMatIntVecInterval(bool* matrix, int32_t* index0, struct Interval* index1) {
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    bool* matrix_data = (bool*)(((int32_t*)matrix) + 2);

    int32_t index0_size = *(int32_t*)index0;
    bool* index0_data = (bool*)(((int32_t*)index0) + 1);
    int32_t index1_size = index1->max - index1->min + 1;

    int32_t* ret = malloc(sizeof(bool) * (index0_size) * (index1_size) + sizeof(int32_t));
    bool* ret_data = (bool*)(ret + 2);
    *ret = index0_size;
    *(ret + 1) =  index1_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        for (size_t j = 0 ; j < index1_size; j++) {
            int32_t k = index0_data[i] - 1;
            int32_t l = index1->min + j - 1;
            if (k >= matrix_size0 || l >= matrix_size1) {
                matrixIndexOutBound(matrix_size0, matrix_size1, k, l);
            }
            ret_data[k * index1_size + l] = matrix_data[k * matrix_size1 + l];
        }
    }

    //free(index1);
    return (bool*)ret;
}

int8_t* getCharMatIntIntVec(int8_t* matrix, int32_t index0, int32_t* index1) {
    index0--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    int8_t* matrix_data = (int8_t*)(((int32_t*)matrix) + 2);

    int32_t index1_size = *(int32_t*)index1;
    int8_t* index1_data = (int8_t*)(((int32_t*)index1) + 1);

    int32_t* ret = malloc(sizeof(int8_t) * (index1_size) + sizeof(int32_t));
    int8_t* ret_data = (int8_t*)(ret + 1);
    *ret = index1_size;
    
    for (size_t i = 0 ; i < index1_size; i++) {
        int32_t j = index1_data[i] - 1;
        if (index0 >= matrix_size0 || j >= matrix_size1) {
            matrixIndexOutBound(matrix_size0, matrix_size1, index0, j);
        }
        ret_data[i] = matrix_data[index0 * matrix_size1 + j];
    }

    return (int8_t*)ret;
}
int8_t* getCharMatIntInterval(int8_t* matrix, int32_t index0, struct Interval* index1) {
    index0--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    int8_t* matrix_data = (int8_t*)(((int32_t*)matrix) + 2);

    int32_t index1_size = index1->max - index1->min + 1;

    int32_t* ret = malloc(sizeof(int8_t) * (index1_size) + sizeof(int32_t));
    int8_t* ret_data = (int8_t*)(ret + 1);
    *ret = index1_size;
    
    for (size_t i = 0 ; i < index1_size; i++) {
        int32_t j = index1->min + i - 1;
        if (index0 >= matrix_size0 || j >= matrix_size1) {
            matrixIndexOutBound(matrix_size0, matrix_size1, index0, j);
        }
        ret_data[i] = matrix_data[index0 * matrix_size1 + j];
    }

    //free(index1);
    return (int8_t*)ret;
}
int8_t* getCharMatIntVecInt(int8_t* matrix, int32_t* index0, int32_t index1) {
    index1--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    int8_t* matrix_data = (int8_t*)(((int32_t*)matrix) + 2);

    int32_t index0_size = *(int32_t*)index0;
    int8_t* index0_data = (int8_t*)(((int32_t*)index0) + 1);

    int32_t* ret = malloc(sizeof(int8_t) * (index0_size) + sizeof(int32_t));
    int8_t* ret_data = (int8_t*)(ret + 1);
    *ret = index0_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        int32_t j = index0_data[i] - 1;
        if (j >= matrix_size0 || index1 >= matrix_size1) {
            matrixIndexOutBound(matrix_size0, matrix_size1, j, index1);
        }
        ret_data[i] = matrix_data[j * matrix_size1 + index1];
    }
    free(index0);
    return (int8_t*)ret;
}
int8_t* getCharMatIntervalInt(int8_t* matrix, struct Interval* index0, int32_t index1) {
    index1--;
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    int8_t* matrix_data = (int8_t*)(((int32_t*)matrix) + 2);

    int32_t index0_size = index0->max - index0->min + 1;

    int32_t* ret = malloc(sizeof(int8_t) * (index0_size) + sizeof(int32_t));
    int8_t* ret_data = (int8_t*)(ret + 1);
    *ret = index0_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        int32_t j = index0->min + i - 1;
        if (j >= matrix_size0 || index1 >= matrix_size1) {
            matrixIndexOutBound(matrix_size0, matrix_size1, j, index1);
        }
        ret_data[i] = matrix_data[j * matrix_size1 + index1];
    }

    //free(index0);
    return (int8_t*)ret;
}
int8_t* getCharMatIntervalInterval(int8_t* matrix, struct Interval* index0, struct Interval* index1) {
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    int8_t* matrix_data = (int8_t*)(((int32_t*)matrix) + 2);

    int32_t index0_size = index0->max - index0->min + 1;
    int32_t index1_size = index1->max - index1->min + 1;

    int32_t* ret = malloc(sizeof(int8_t) * (index0_size) * (index1_size) + sizeof(int32_t));
    int8_t* ret_data = (int8_t*)(ret + 2);
    *ret = index0_size;
    *(ret + 1) =  index1_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        for (size_t j = 0 ; j < index1_size; j++) {
            int32_t k = index0->min + i - 1;
            int32_t l = index1->min + j - 1;
            if (k >= matrix_size0 || l >= matrix_size1) {
                matrixIndexOutBound(matrix_size0, matrix_size1, k, l);
            }
            ret_data[k * index1_size + l] = matrix_data[k * matrix_size1 + l];
        }
    }

    //free(index0);
    //free(index1);
    return (int8_t*)ret;
}
int8_t* getCharMatIntVecIntVec(int8_t* matrix, int32_t* index0, int32_t* index1) {
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    int8_t* matrix_data = (int8_t*)(((int32_t*)matrix) + 2);

    int32_t index0_size = *(int32_t*)index0;
    int8_t* index0_data = (int8_t*)(((int32_t*)index0) + 1);
    int32_t index1_size = *(int32_t*)index1;
    int8_t* index1_data = (int8_t*)(((int32_t*)index1) + 1);

    int32_t* ret = malloc(sizeof(int8_t) * (index0_size) * (index1_size) + sizeof(int32_t));
    int8_t* ret_data = (int8_t*)(ret + 2);
    *ret = index0_size;
    *(ret + 1) =  index1_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        for (size_t j = 0 ; j < index1_size; j++) {
            int32_t k = index0_data[i] - 1;
            int32_t l = index1_data[j] - 1;
            if (k >= matrix_size0 || l >= matrix_size1) {
                matrixIndexOutBound(matrix_size0, matrix_size1, k, l);
            }
            ret_data[k * index1_size + l] = matrix_data[k * matrix_size1 + l];
        }
    }

    return (int8_t*)ret;
}

int8_t* getCharMatIntervalIntVec(int8_t* matrix, struct Interval* index0, int32_t* index1) {
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    int8_t* matrix_data = (int8_t*)(((int32_t*)matrix) + 2);

    int32_t index0_size = index0->max - index0->min + 1;
    int32_t index1_size = *(int32_t*)index1;
    int8_t* index1_data = (int8_t*)(((int32_t*)index1) + 1);

    int32_t* ret = malloc(sizeof(int8_t) * (index0_size) * (index1_size) + sizeof(int32_t));
    int8_t* ret_data = (int8_t*)(ret + 2);
    *ret = index0_size;
    *(ret + 1) =  index1_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        for (size_t j = 0 ; j < index1_size; j++) {
            int32_t k = index0->min + i - 1;
            int32_t l = index1_data[j] - 1;
            if (k >= matrix_size0 || l >= matrix_size1) {
                matrixIndexOutBound(matrix_size0, matrix_size1, k, l);
            }
            ret_data[k * index1_size + l] = matrix_data[k * matrix_size1 + l];
        }
    }

    //free(index0);
    return (int8_t*)ret;
}
int8_t* getCharMatIntVecInterval(int8_t* matrix, int32_t* index0, struct Interval* index1) {
    int32_t matrix_size0 = *(int32_t*)matrix;
    int32_t matrix_size1 = *(((int32_t*)matrix)+ 1);
    int8_t* matrix_data = (int8_t*)(((int32_t*)matrix) + 2);

    int32_t index0_size = *(int32_t*)index0;
    int8_t* index0_data = (int8_t*)(((int32_t*)index0) + 1);
    int32_t index1_size = index1->max - index1->min + 1;

    int32_t* ret = malloc(sizeof(int8_t) * (index0_size) * (index1_size) + sizeof(int32_t));
    int8_t* ret_data = (int8_t*)(ret + 2);
    *ret = index0_size;
    *(ret + 1) =  index1_size;
    
    for (size_t i = 0 ; i < index0_size; i++) {
        for (size_t j = 0 ; j < index1_size; j++) {
            int32_t k = index0_data[i] - 1;
            int32_t l = index1->min + j - 1;
            if (k >= matrix_size0 || l >= matrix_size1) {
                matrixIndexOutBound(matrix_size0, matrix_size1, k, l);
            }
            ret_data[k * index1_size + l] = matrix_data[k * matrix_size1 + l];
        }
    }

    //free(index1);
    return (int8_t*)ret;
}