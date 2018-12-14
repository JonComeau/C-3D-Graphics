#ifndef THREEDEE_S_T_R_H
#define THREEDEE_S_T_R_H

#include "threedee/types.h"
#include "threedee/matrix.h"

float sin_look[360+1], cos_look[360+1];

void global_rotate(mat4x4_ptr rot_x, mat4x4_ptr rot_y, mat4x4_ptr rot_z, float x_theta, float y_theta, float z_theta);
void build_look_up_tables(void);
void rotate_obj(object_ptr obj, float x_theta, float y_theta, float z_theta);
void trans_obj(object_ptr obj, float x, float y, float z);
void scale_obj(object_ptr obj, float x_scale, float y_scale, float z_scale);


#endif //THREEDEE_S_T_R_H
