#include <math.h>
#include <stddef.h>
#include "threedee/types.h"

float vec3f_norm(vec3f_ptr self) {
    return sqrtf(self->x*self->x+self->y*self->y+self->z*self->z);
}

vec3f_ptr vec3f_normalize(vec3f_ptr self) {
    return vec3f_float_mult(self, 1 / vec3f_norm(self));
}

vec3f_ptr vec3f_normalize_l(vec3f_ptr self, float l) {
    return vec3f_float_mult(self, l / vec3f_norm(self));
}

float vec3f_vec3f_mult(vec3f_ptr lhs, vec3f_ptr rhs) {
    return lhs->x*rhs->x + lhs->y*rhs->y + lhs->z*rhs->z;
}

vec3f_ptr vec3f_vec3f_add(vec3f_ptr lhs, vec3f_ptr rhs) {
    static vec3f ret;
    ret.x = lhs->x + rhs->x;
    ret.y = lhs->y + rhs->y;
    ret.z = lhs->z + rhs->z;
    return &ret;
}

vec3f_ptr vec3f_vec3f_cross(vec3f_ptr lhs, vec3f_ptr rhs) {
    static vec3f ret;
    ret.x = lhs->y * rhs->z - lhs->z * rhs->y;
    ret.y = lhs->z * rhs->x - lhs->x * rhs->z;
    ret.z = lhs->x * rhs->y - lhs->y * rhs->x;
    return &ret;
}

vec3f_ptr vec3f_vec3f_sub(vec3f_ptr lhs, vec3f_ptr rhs) {
    static vec3f ret;
    ret.x = lhs->x - rhs->x;
    ret.y = lhs->y - rhs->y;
    ret.z = lhs->z - rhs->z;
    return &ret;
}

vec3f_ptr vec3f_float_mult(vec3f_ptr lhs, float scalar) {
    static vec3f ret;

    ret.x = lhs->x * scalar;
    ret.y = lhs->y * scalar;
    ret.z = lhs->z * scalar;

    return &ret;
}

vec3f_ptr mat4x4_vec3f_mult(mat4x4_ptr mat, vec3f_ptr vec) {
    static vec3f ret;
    float w;

    ret.x = vec->x * mat->m[0][0] + vec->x * mat->m[1][0] + vec->z * mat->m[2][0] + mat->m[3][0];
    ret.y = vec->x * mat->m[0][1] + vec->x * mat->m[1][1] + vec->z * mat->m[2][1] + mat->m[3][1];
    ret.z = vec->x * mat->m[0][2] + vec->x * mat->m[1][2] + vec->z * mat->m[2][2] + mat->m[3][2];
    w = vec->x * mat->m[0][3] + vec->x * mat->m[1][3] + vec->z * mat->m[2][3] + mat->m[3][3];

    if (w != 0.0f) {
        ret.x /= w;
        ret.y /= w;
        ret.z /= w;
    }

    return &ret;
}
