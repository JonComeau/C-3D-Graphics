#ifndef THREEDEE_DRAW_H
#define THREEDEE_DRAW_H

#include "threedee/types.h"

void set_viewport(int x, int y, int w, int h);
void set_projection(float coeff);
void lookat(vec3f eye, vec3f center, vec3f up);

#endif //THREEDEE_DRAW_H
