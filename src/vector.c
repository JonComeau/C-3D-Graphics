#include <math.h>
#include "vector.h"

void vector3_add(vector3* rhs, vector3* lhs) {
    rhs->x += lhs->x;
    rhs->y += lhs->y;
    rhs->z += lhs->z;
}

void vector3_subtract(vector3* rhs, vector3* lhs) {
    rhs->x -= lhs->x;
    rhs->y -= lhs->y;
    rhs->z -= lhs->z;
}

void vector3_apply_scalar(vector3* self, float scalar) {
    self->x *= scalar;
    self->y *= scalar;
    self->z *= scalar;
}

float vector3_length(vector3* self) {
    return sqrtf((self->x * self->x) + (self->y * self->y) + (self->z * self->z));
}

float vector3_dot(vector3* rhs, vector3* lhs) {
    return (rhs->x * lhs->x) + (rhs->y * lhs->y) + (rhs->z * lhs->z);
}

vector3* vector3_cross(vector3* rhs, vector3* lhs) {
    static vector3 result;

    result.x = (rhs->y * lhs->z) - (rhs->z * lhs->y);
    result.y = (rhs->x * lhs->z) - (rhs->z * lhs->x);
    result.z = (rhs->x * lhs->y) - (rhs->y * lhs->x);

    return &result;
}

void vector3_normalize(vector3* self) {
    vector3_apply_scalar(self, powf(vector3_length(self), -1));
}

void vector2_add(vector2* rhs, vector2* lhs) {
    rhs->x += lhs->x;
    rhs->y += lhs->y;
}

void vector2_subtract(vector2* rhs, vector2* lhs) {
    rhs->x -= lhs->x;
    rhs->y -= lhs->y;
}

void vector2_apply_scalar(vector2* rhs, float scalar) {
    rhs->x *= scalar;
    rhs->y *= scalar;
}

float vector2_dot(vector2* rhs, vector2* lhs) {
    return (rhs->x * lhs->x) + (rhs->y * lhs->y);
}