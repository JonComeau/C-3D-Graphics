#ifndef THREEDEE_S_T_R_H
#define THREEDEE_S_T_R_H

#include "threedee/types.h"

float sin_look[360+1],
      cos_look[360+1];

void build_lookup_tables();
void rotate_object(object_ptr object, int angle_x, int angle_y, int angle_z);

#endif //THREEDEE_S_T_R_H
