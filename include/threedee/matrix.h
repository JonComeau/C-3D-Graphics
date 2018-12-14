#ifndef THREEDEE_MATRIX_H
#define THREEDEE_MATRIX_H

#include "types.h"

void mat_identity_4x4(mat4x4_ptr a);
void mat_zero_4x4(mat4x4_ptr a);
void mat_copy_4x4(mat4x4_ptr source, mat4x4_ptr destination);
void mat_print_4x4(mat4x4_ptr a);
mat4x4 mat_mul_4x4_4x4(mat4x4 a, mat4x4 b);
mat4x4 mat_add_4x4_4x4(mat4x4 a, mat4x4 b);
vec4f mat_mul_4x4_4x1(mat4x4 a, vec4f b);

#endif //THREEDEE_MATRIX_H