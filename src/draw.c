#include <stdlib.h>
#include "threedee/draw.h"

void draw_line(pbitmap map, int x1, int y1, int x2, int y2, color_ptr col) {
    int x, y, dx, dy, dx1, dy1, px, py, xe, ye, index;

    dx = x2 - x1;
    dy = y2 - y1;

    dx1 = abs(dx);
    dy1 = abs(dy);

    px = 2 * dy1 - dx1;
    py = 2 * dx1 - dy1;

    if (dy1 <= dx1) {
        if (dx >= 0) {
            x = x1;
            y = y1;
            xe = x2;
        } else {
            x = x2;
            y = y2;
            xe = x1;
        }

        set(map, x, y, col);

        for (index = 0; x < xe; index++) {
            x = x + 1;

            if (px < 0) {
                px = px + 2 * y1;
            } else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                    y = y + 1;
                } else {
                    y = y - 1;
                }
                px = px + 2 * (dy1 - dx1);
            }

            set(map, x, y, col);
        }
    } else {
        if (dy >= 0) {
            x = x1;
            y = y1;
            ye = y2;
        } else {
            x = x2;
            y = y2;
            ye = y1;
        }

        set(map, x, y, col);

        for (index = 0; y < ye; index++) {
            y = y + 1;
            if (py <= 0) {
                py = py + 2 * dx1;
            } else {
                if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
                    x = x + 1;
                } else {
                    x = x - 1;
                }

                set(map, x, y, col);
            }
        }
    }
}

void draw_tri(pbitmap map, int x1, int y1, int x2, int y2, int x3, int y3, color_ptr col) {
    draw_line(map, x1, y1, x2, y2, col);
    draw_line(map, x2, y2, x3, y3, col);
    draw_line(map, x3, y3, x1, y1, col);
}