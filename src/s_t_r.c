#include <math.h>
#include "threedee/s_t_r.h"

void rotate_object();

void build_look_up_tables(void) {
    int angle;
    float rad;

    for (angle = 0; angle <= 360; angle++) {
        rad = (3.14159f * (float)angle / 180.0f);

        cos_look[angle] = cosf(rad);
        sin_look[angle] = sinf(rad);
    }
}

void rotate_obj(object_ptr obj, float x_theta, float y_theta, float z_theta) {
    mat4x4 rot_x, rot_y, rot_z, rot;

    mat_identity_4x4(&rot_x);
    mat_identity_4x4(&rot_y);
    mat_identity_4x4(&rot_z);

    rot_x.m[0][0] = cosf(x_theta);
    rot_x.m[0][1] = sinf(x_theta);
    rot_x.m[1][0] = -sinf(x_theta);
    rot_x.m[1][1] = cosf(x_theta);

    rot_y.m[1][1] = cosf(y_theta);
    rot_y.m[1][2] = sinf(y_theta);
    rot_y.m[2][1] = -sinf(y_theta);
    rot_y.m[2][2] = cosf(y_theta);

    rot_z.m[0][0] = cosf(y_theta);
    rot_z.m[2][0] = sinf(y_theta);
    rot_z.m[0][2] = -sinf(y_theta);
    rot_z.m[2][2] = cosf(y_theta);

    rot = mat_mul_4x4_4x4(rot_x, mat_mul_4x4_4x4(rot_y, rot_z));

    for (int index = 0; index < obj->vert_count; index++) {
        vec4f temp = {obj->verts[index].x,
                      obj->verts[index].y,
                      obj->verts[index].z,
                      1};

        temp = mat_mul_4x4_4x1(rot, temp);

        obj->verts[index].x = temp.array[0];
        obj->verts[index].y = temp.array[1];
        obj->verts[index].z = temp.array[2];
    }
}

void trans_obj(object_ptr obj, float x, float y, float z) {
    for (int index = 0; index < obj->vert_count; index++) {
        obj->verts[index].x += x;
        obj->verts[index].y += y;
        obj->verts[index].z += z;
    }
}

void scale_obj(object_ptr obj, float x_scale, float y_scale, float z_scale) {
    for (int index = 0; index < obj->vert_count; index++) {
        obj->verts[index].x *= x_scale;
        obj->verts[index].y *= y_scale;
        obj->verts[index].z *= z_scale;
    }
}