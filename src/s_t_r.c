#include <math.h>
#include "threedee/types.h"
#include "threedee/matrix.h"
#include "threedee/s_t_r.h"

/// This function builds the sin/cos angle lookups for quick access
void build_lookup_tables() {
    int angle;
    float rad;

    // Generate the tables
    for (angle = 0; angle <= 360; angle++) {
        // convert deg to rad
        rad = (float)(3.14159 * (float)angle/(float)180);

        cos_look[angle] = cosf(rad);
        sin_look[angle] = sinf(rad);
    }
}

/// This function rotates an object relative to its local coordinate system
void rotate_object(object_ptr object, int angle_x, int angle_y, int angle_z) {
    int index, product = 0;
    matrix_4x4 rotate_x,
               rotate_y,
               rotate_z,
               rotate,
               temp;
    float temp_x, temp_y, temp_z;

    // Test if rotation is needed at all
    if (angle_x == 0 && angle_y == 0 && angle_z == 0) return;

    // Create identity matrix
    mat_identity_4x4(rotate);

    // Create X rotation matrix
    if (angle_x) {
        mat_identity_4x4(rotate_x);

        rotate_x[1][1] =  cos_look[angle_x];
        rotate_x[1][2] =  sin_look[angle_x];
        rotate_x[2][1] = -sin_look[angle_x];
        rotate_x[2][2] =  cos_look[angle_x];
    }

    // Create Y rotation matrix
    if (angle_y) {
        mat_identity_4x4(rotate_y);

        rotate_y[0][0] =  cos_look[angle_y];
        rotate_y[0][2] = -sin_look[angle_y];
        rotate_y[2][0] =  sin_look[angle_y];
        rotate_y[2][2] =  cos_look[angle_y];
    }

    // Create Z rotation matrix
    if (angle_z) {
        mat_identity_4x4(rotate_z);

        rotate_z[0][0] =  cos_look[angle_z];
        rotate_z[0][1] =  sin_look[angle_z];
        rotate_z[1][0] = -sin_look[angle_z];
        rotate_z[1][1] =  cos_look[angle_z];
    }

    // Compute the final rotational matrix by setting bits and switching through
    // every possible configuration

    if (angle_x) product|=4;
    if (angle_y) product|=2;
    if (angle_z) product|=1;

    // Case 0 shouldn't happpen
    switch (product) {
        case 1: // final = z
            mat_copy_4x4(rotate_z, rotate);
            break;
        case 2: // final = y
            mat_copy_4x4(rotate_y, rotate);
            break;
        case 3: // final = y*z
            mat_mul_4x4_4x4(rotate_y, rotate_z, rotate);
            break;
        case 4: // final = x
            mat_copy_4x4(rotate_x, rotate);
            break;
        case 5: // final = x*y
            mat_mul_4x4_4x4(rotate_x, rotate_z, rotate);
            break;
        case 6:
            mat_mul_4x4_4x4(rotate_x, rotate_y, rotate);
            break;
        case 7:
            mat_mul_4x4_4x4(rotate_x, rotate_y, temp);
            mat_mul_4x4_4x4(temp, rotate_z, rotate);
            break;
        default:
            break;
    }

    // Multiply each point by transformation matrix
    for (index = 0; index < object->num_vertices; index++) {
        temp_x = object->vertices_local[index].x * rotate[0][0] +
                 object->vertices_local[index].y * rotate[1][0] +
                 object->vertices_local[index].z * rotate[2][0];
        temp_y = object->vertices_local[index].x * rotate[0][1] +
                 object->vertices_local[index].y * rotate[1][1] +
                 object->vertices_local[index].z * rotate[2][1];
        temp_z = object->vertices_local[index].x * rotate[0][2] +
                 object->vertices_local[index].y * rotate[1][2] +
                 object->vertices_local[index].z * rotate[2][2];

        object->vertices_local[index].x = temp_x;
        object->vertices_local[index].y = temp_y;
        object->vertices_local[index].z = temp_z;
    }
}