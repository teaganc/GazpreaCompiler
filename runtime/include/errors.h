#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void vectorMatrixMismatchError(int32_t vector_size, int32_t matrix_size);
void vectorSizeMismatchError(int32_t size0, int32_t size1);
void matrixSizeMismatchError(int32_t row0, int32_t col0, int32_t row1, int32_t col1);
void checkNan(float value);
void vectorIndexOutBound(int32_t size, int32_t index);
void matrixIndexOutBound(int32_t size0, int32_t size1, int32_t index0, int32_t index1);
void inputBoolError();
void inputIntError();
void inputFloatError();
void inputCharError();