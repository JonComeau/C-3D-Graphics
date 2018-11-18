#include <stdio.h>
#include "threedee/matrix.h"

// this function creates a 4x4 identity matrix
void mat_identity_4x4(matrix_4x4 a) {
    a[0][1] = a[0][2] = a[0][3] = 0;
    a[1][0] = a[1][2] = a[1][3] = 0;
    a[2][0] = a[2][1] = a[2][3] = 0;
    a[3][0] = a[3][1] = a[3][2] = 0;

    // set main diagonal to 1's
    a[0][0] = a[1][1] = a[2][2] = a[3][3] = 1;
}

// this function zeros out a 4x4 matrix
void mat_zero_4x4(matrix_4x4 a) {
    a[0][0] = a[0][1] = a[0][2] = a[0][3] = 0;
    a[1][0] = a[1][1] = a[1][2] = a[1][3] = 0;
    a[2][0] = a[2][1] = a[2][2] = a[2][3] = 0;
    a[3][0] = a[3][1] = a[3][2] = a[3][3] = 0;
}

// this function copies on 4x4 matrix to another
void mat_copy_4x4(matrix_4x4 source, matrix_4x4 destination) {
    destination[0][0] = source[0][0];
    destination[1][0] = source[1][0];
    destination[2][0] = source[2][0];
    destination[3][0] = source[3][0];
    destination[0][1] = source[0][1];
    destination[1][1] = source[1][1];
    destination[2][1] = source[2][1];
    destination[3][1] = source[3][1];
    destination[0][2] = source[0][2];
    destination[1][2] = source[1][2];
    destination[2][2] = source[2][2];
    destination[3][2] = source[3][2];
    destination[0][3] = source[0][3];
    destination[1][3] = source[1][3];
    destination[2][3] = source[2][3];
    destination[3][3] = source[3][3];
}

// this funtion prints out a 4x4 matrix
void mat_print_4x4(matrix_4x4 a) {
    int row, column;

    for (row = 0; row < 4; row++) {
        printf("\n");
        for (column = 0; column < 4; column++) {
            printf("%f ", a[row][column]);
        }
    }

    printf("\n");
}

// This function multiplies a 4x4 be a 4x4 and stores the result in 4x4
void mat_mul_4x4_4x4(matrix_4x4 a, matrix_4x4 b, matrix_4x4 result) {
    int index_i, index_j, index_k;
    float sum;

    for (index_i = 0; index_i < 4; index_i++) {
        for (index_j = 0; index_j < 4; index_j++) {
            sum = 0;
            for (index_k = 0; index_k < 4; index_k++) {
                sum += a[index_i][index_k] * b[index_k][index_j];
                result[index_i][index_j] = sum;
            }
        }
    }
}