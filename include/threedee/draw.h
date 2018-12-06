#ifndef THREEDEE_DRAW_H
#define THREEDEE_DRAW_H

#include "threedee/bitmap.h"
#include "threedee/types.h"

void draw_tri(pbitmap map, int x1, int y1, int x2, int y2, int x3, int y3, color_ptr col);
void draw_line(pbitmap map, int x1, int y1, int x2, int y2, color_ptr col);

#endif //THREEDEE_DRAW_H
