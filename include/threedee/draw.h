#ifndef THREEDEE_DRAW_H
#define THREEDEE_DRAW_H

#include "threedee/bitmap.h"
#include "threedee/types.h"

void set_viewport(int x, int y, int w, int h);
void set_projection(float coeff);
void lookat(vec3f_ptr eye, vec3f_ptr center, vec3f_ptr up);
vec3f_ptr barycentric(vec2f_ptr a, vec2f_ptr b, vec2f_ptr c, vec2f_ptr p);

void line(pbitmap bitmap, int x0, int y0, int x1, int y1, color_ptr color);

#endif //THREEDEE_DRAW_H
