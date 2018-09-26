#ifndef THREEDEE_MATH_H
#define THREEDEE_MATH_H

#include "types.h"

void make_vector_3d(point_3d_ptr init, point_3d_ptr trem, vector_3d_ptr result);
float vector_mag_3d(vector_3d_ptr v);
float dot_product_3d(vector_3d_ptr u, vector_3d_ptr v);
void cross_product_3d(vector_3d_ptr u, vector_3d_ptr v, vector_3d_ptr normal);

#endif //THREEDEE_MATH_H
