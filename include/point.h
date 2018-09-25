#ifndef THREEDEE_POINT_H
#define THREEDEE_POINT_H

#include "vector.h"

typedef struct point3 {
    float x, y, z;
} point3;

typedef struct point2 {
    float x, y;
} point2;

vector3* vector3_from_points(point3* rhs, point3* lhs);

#endif //THREEDEE_POINT_H
