#ifndef THREEDEE_MATRIX_H
#define THREEDEE_MATRIX_H

#include "types.h"

void mat_identity_4x4(matrix_4x4 a);
void mat_zero_4x4(matrix_4x4 a);
void mat_copy_4x4(matrix_4x4 source, matrix_4x4 destination);
void mat_print_4x4(matrix_4x4 a);
void mat_print_1x4(matrix_1x4 a);
void mat_mul_4x4_4x4(matrix_4x4 a, matrix_4x4 b, matrix_4x4 result);
void mat_mul_1x4_4x4(matrix_1x4 a, matrix_4x4 b, matrix_1x4 result);

#endif //THREEDEE_MATRIX_H