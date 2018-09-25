#include "vector.h"
#include "point.h"

vector3* vector3_from_points(point3* p1, point3* p2) {
    static vector3 result;

    result.x = p1->x - p2->x;
    result.y = p1->y - p2->y;
    result.z = p1->z - p2->z;

    return &result;
}