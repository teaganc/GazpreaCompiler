#include "errors.h"
#include <math.h>

// TODO: improve on this error
void vectorMatrixMismatchError(int32_t vector_size, int32_t matrix_size) {
  fprintf(stderr, "Size mismatch error: cannot write to matrix of size %u with a vector of size %u\n", matrix_size, vector_size);
  exit(1);
}
void vectorSizeMismatchError(int32_t size0, int32_t size1) {
  fprintf(stderr, "Size mismatch error: Attempting to operate on different vector sizes of %u and %u\n"
    , size0, size1);
  exit(1);
}
void matrixSizeMismatchError(int32_t row0, int32_t col0, int32_t row1, int32_t col1) {
  fprintf(stderr, "Size mismatch error: Attempting to operate on different matrix sizes of [%u, %u] and [%u, %u]\n"
    , row0, col0, row1, col1);
  exit(1);
}
void checkNan(float value) {
  if (isnan(value)) {
    fprintf(stderr, "Nan error\n");
    exit(1);
  }
}
void vectorIndexOutBound(int32_t size, int32_t index) {
  fprintf(stderr, "Vector index out of bounds. Size was %u but index was %u\n", size, index);
  exit(1);
}
void matrixIndexOutBound(int32_t size0, int32_t size1, int32_t index0, int32_t index1) {
  fprintf(stderr, "Matrix index out of bounds. Size was of [%u, %u] but the index was of [%u, %u]\n"
    , size0, size1, index0, index1);
  exit(1);
}
void inputBoolError() {
  //printf("ERROR: Input expected a boolean\n");
  //exit(-1);
}
void inputIntError() {
  //printf("ERROR: Input expected a integer\n");
  //exit(-1);
}
void inputFloatError() {
  //printf("ERROR: Input expected a float\n");
  //exit(-1);
}
void inputCharError() {
  //printf("ERROR: Input expected a character\n");
  //exit(-1);
}