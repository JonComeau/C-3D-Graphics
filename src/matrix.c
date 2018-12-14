#include <stdio.h>
#include "threedee/matrix.h"

// this function creates a 4x4 identity matrix
void mat_identity_4x4(mat4x4_ptr a) {
    a->m[0][1] = a->m[0][2] = a->m[0][3] = 0;
    a->m[1][0] = a->m[1][2] = a->m[1][3] = 0;
    a->m[2][0] = a->m[2][1] = a->m[2][3] = 0;
    a->m[3][0] = a->m[3][1] = a->m[3][2] = 0;

    // set main diagonal to 1's
    a->m[0][0] = a->m[1][1] = a->m[2][2] = a->m[3][3] = 1;
}

// this function zeros out a 4x4 matrix
void mat_zero_4x4(mat4x4_ptr a) {
    a->m[0][0] = a->m[0][1] = a->m[0][2] = a->m[0][3] = 0;
    a->m[1][0] = a->m[1][1] = a->m[1][2] = a->m[1][3] = 0;
    a->m[2][0] = a->m[2][1] = a->m[2][2] = a->m[2][3] = 0;
    a->m[3][0] = a->m[3][1] = a->m[3][2] = a->m[3][3] = 0;
}

// this function copies on 4x4 matrix to another
void mat_copy_4x4(mat4x4_ptr source, mat4x4_ptr destination) {
    destination->m[0][0] = source->m[0][0];
    destination->m[1][0] = source->m[1][0];
    destination->m[2][0] = source->m[2][0];
    destination->m[3][0] = source->m[3][0];
    destination->m[0][1] = source->m[0][1];
    destination->m[1][1] = source->m[1][1];
    destination->m[2][1] = source->m[2][1];
    destination->m[3][1] = source->m[3][1];
    destination->m[0][2] = source->m[0][2];
    destination->m[1][2] = source->m[1][2];
    destination->m[2][2] = source->m[2][2];
    destination->m[3][2] = source->m[3][2];
    destination->m[0][3] = source->m[0][3];
    destination->m[1][3] = source->m[1][3];
    destination->m[2][3] = source->m[2][3];
    destination->m[3][3] = source->m[3][3];
}

// this funtion prints out a 4x4 matrix
void mat_print_4x4(mat4x4_ptr a) {
    int row, column;

    for (row = 0; row < 4; row++) {
        printf("\n");
        for (column = 0; column < 4; column++) {
            printf("%f ", a->m[row][column]);
        }
    }

    printf("\n");
}

// This function multiplies a 4x4 be a 4x4 and stores the result in 4x4
mat4x4 mat_mul_4x4_4x4(mat4x4 a, mat4x4 b) {
    mat4x4 result;
    int index_i, index_j, index_k;
    float sum;

    for (index_i = 0; index_i < 4; index_i++) {
        for (index_j = 0; index_j < 4; index_j++) {
            sum = 0;
            for (index_k = 0; index_k < 4; index_k++) {
                sum += a.m[index_i][index_k] * b.m[index_k][index_j];
                result.m[index_i][index_j] = sum;
            }
        }
    }

    return result;
}

mat4x4 mat_add_4x4_4x4(mat4x4 a, mat4x4 b) {
    return (mat4x4) {
            a.m[0][0] + b.m[0][0],
            a.m[0][1] + b.m[0][1],
            a.m[0][2] + b.m[0][2],
            a.m[0][3] + b.m[0][3],
            a.m[1][0] + b.m[0][0],
            a.m[1][1] + b.m[0][1],
            a.m[1][2] + b.m[0][2],
            a.m[1][3] + b.m[0][3],
            a.m[2][0] + b.m[0][0],
            a.m[2][1] + b.m[0][1],
            a.m[2][2] + b.m[0][2],
            a.m[2][3] + b.m[0][3],
            a.m[3][0] + b.m[0][0],
            a.m[3][1] + b.m[0][1],
            a.m[3][2] + b.m[0][2],
            a.m[3][3] + b.m[0][3]
    };
}

vec4f mat_mul_4x4_4x1(mat4x4 mat, vec4f vec) {
    return (vec4f){
            mat.m[0][0] * vec.array[0] +
            mat.m[0][1] * vec.array[1] +
            mat.m[0][2] * vec.array[2] +
            mat.m[0][3] * vec.array[3],
            mat.m[1][0] * vec.array[0] +
            mat.m[1][1] * vec.array[1] +
            mat.m[1][2] * vec.array[2] +
            mat.m[1][3] * vec.array[3],
            mat.m[2][0] * vec.array[0] +
            mat.m[2][1] * vec.array[1] +
            mat.m[2][2] * vec.array[2] +
            mat.m[2][3] * vec.array[3],
            mat.m[3][0] * vec.array[0] +
            mat.m[3][1] * vec.array[1] +
            mat.m[3][2] * vec.array[2] +
            mat.m[3][3] * vec.array[3]
    };
}