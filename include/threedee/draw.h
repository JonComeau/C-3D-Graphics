#ifndef THREEDEE_DRAW_H
#define THREEDEE_DRAW_H

#include "threedee/bitmap.h"
#include "threedee/types.h"

void draw_tri(pbitmap map, vec2i_ptr t0, vec2i_ptr t1, vec2i_ptr t2, color_ptr col);
void draw_line(pbitmap map, int x0, int y0, int x1, int y1, color_ptr col);

#endif //THREEDEE_DRAW_H
