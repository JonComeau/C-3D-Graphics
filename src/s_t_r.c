#include <math.h>
#include "threedee/s_t_r.h"

void global_rotate(mat4x4_ptr rot_x, mat4x4_ptr rot_y, mat4x4_ptr rot_z, float x_theta, float y_theta, float z_theta) {
    // Rotation z
    rot_z->m[0][0] = rot_z->m[1][1] = cosf(z_theta);
    rot_z->m[0][1] = sinf(z_theta);
    rot_z->m[1][0] = -rot_z->m[0][1];
    rot_z->m[2][2] = rot_z->m[3][3] = 1;

    // Rotation x
    rot_x->m[0][0] = rot_x->m[3][3] = 1;
    rot_x->m[1][1] = rot_x->m[2][2] = cosf(x_theta);
    rot_x->m[1][2] = sinf(x_theta);
    rot_x->m[2][1] = -sinf(x_theta);
}