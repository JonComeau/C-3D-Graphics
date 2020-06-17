#include <math.h>
#include <stdio.h>
#include <stddef.h>
#include "threedee/types.h"

float vec3f_norm(vec3f self) {
    return sqrtf(self.x*self.x+self.y*self.y+self.z*self.z);
}

vec3f vec3f_normalize(vec3f self) {
    return vec3f_float_mult(self, 1 / vec3f_norm(self));
}

vec3f vec3f_normalize_l(vec3f self, float l) {
    return vec3f_float_mult(self, l / vec3f_norm(self));
}

float vec3f_vec3f_mult(vec3f lhs, vec3f rhs) {
    return lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
}

vec3f vec3f_vec3f_add(vec3f lhs, vec3f rhs) {
    return (vec3f){
        lhs.x + rhs.x,
        lhs.y + rhs.y,
        lhs.z + rhs.z
    };
}

vec3f vec3f_vec3f_sub(vec3f lhs, vec3f rhs) {
    return (vec3f) {
        lhs.x - rhs.x,
        lhs.y - rhs.y,
        lhs.z - rhs.z
    };
}

vec3f vec3f_vec3f_cross(vec3f lhs, vec3f rhs) {
    return (vec3f){
        lhs.y * rhs.z - lhs.z * rhs.y,
        lhs.z * rhs.x - lhs.x * rhs.z,
        lhs.x * rhs.y - lhs.y * rhs.x
    };
}

vec3f vec3f_float_mult(vec3f lhs, float scalar) {
    return (vec3f){lhs.x * scalar, lhs.y * scalar, lhs.z * scalar};
}

float vec3f_vec3f_dot(vec3f lhs, vec3f rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

vec3f mat4x4_vec3f_mult(mat4x4 mat, vec3f vec) {
    vec3f ret;
    float w;

    ret = (vec3f){
        vec.x * mat.m[0][0] + vec.x * mat.m[1][0] + vec.z * mat.m[2][0] + mat.m[3][0],
        vec.x * mat.m[0][1] + vec.x * mat.m[1][1] + vec.z * mat.m[2][1] + mat.m[3][1],
        vec.x * mat.m[0][2] + vec.x * mat.m[1][2] + vec.z * mat.m[2][2] + mat.m[3][2]
    };
    w = vec.x * mat.m[0][3] + vec.x * mat.m[1][3] + vec.z * mat.m[2][3] + mat.m[3][3];

    if (w != 0.0f) {
        ret.x /= w;
        ret.y /= w;
        ret.z /= w;
    }

    return ret;
}

vec2i vec2i_vec2i_add(vec2i lhs, vec2i rhs) {
    return (vec2i){lhs.x + rhs.x, lhs.y + rhs.y};
}

vec2i vec2i_vec2i_sub(vec2i lhs, vec2i rhs) {
    return (vec2i){lhs.x - rhs.x, lhs.y - rhs.y};
}

vec2i vec2i_float_mult(vec2i self, float scalar) {
    return (vec2i){self.x * scalar, self.y * scalar};
}

void print_obj(object obj) {
    int i;

    if (obj.vert_count) {
        printf("Verts:\n");

        for (i = 0; i < obj.vert_count; i++) {
            printf("%i: (%f, %f, %f)\n", i, obj.verts[i].x, obj.verts[i].y, obj.verts[i].z);
        }
    }

    if (obj.vert_count) {
        printf("\nFaces:\n");

        for (i = 0; i < obj.face_count; i++) {
            printf("%i: (%i, %i, %i)\n", i, obj.faces[i].v[0], obj.faces[i].v[1], obj.faces[i].v[2]);
        }
    }
}