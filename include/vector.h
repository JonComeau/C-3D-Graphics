//
// Created by vylly on 9/24/2018.
//

#ifndef THREEDEE_VECTOR_H
#define THREEDEE_VECTOR_H

typedef struct vector3 {
    float x, y, z;
} vector3;

typedef struct vector2 {
    float x, y;
} vector2;

void vector3_add(vector3* rhs, vector3* lhs);
void vector3_subtract(vector3* rhs, vector3* lhs);
void vector3_apply_scalar(vector3* self, float scalar);
float vector3_length(vector3* self);
float vector3_dot(vector3* rhs, vector3* lhs);
vector3* vector3_cross(vector3* rhs, vector3* lhs);
void vector3_normalize(vector3* self);

void vector2_add(vector2* rhs, vector2* lhs);
void vector2_subtract(vector2* rhs, vector2* lhs);
void vector2_apply_scalar(vector2* self, float scalar);
float vector2_dot(vector2* rhs, vector2* lhs);

#endif //THREEDEE_VECTOR_H
