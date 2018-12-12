#include <stdlib.h>
#include <string.h>
#include "threedee/draw.h"

void draw_tri(pbitmap map, vec2i t0, vec2i t1, vec2i t2, color_ptr col) {
    vec2i temp, a, b;
    int total_height, index, jndex, seg_height;
    char second_half;
    float alpha, beta;

    if (t0.y == t1.y && t0.y == t2.y) {
        return;
    }

    if (t0.y > t1.y) {
        temp = t0;
        t0 = t1;
        t1 = temp;
    }

    if (t0.y > t1.y) {
        temp = t0;
        t0 = t2;
        t2 = temp;
    }

    if (t1.y > t2.y) {
        temp = t1;
        t1 = t2;
        t2 = temp;
    }

    total_height = t2.y - t0.y;

    for (index = 0; index < total_height; index++) {
        second_half = index > t1.y - t0.y || t1.y == t0.y;
        seg_height = second_half ? t2.y - t1.y : t1.y - t0.y;
        alpha = (float) index / total_height;
        beta = (float) (index - (second_half ? t1.y - t0.y : 0)) / seg_height;
        a = vec2i_vec2i_add(t0, vec2i_float_mult(vec2i_vec2i_sub(t2, t0), alpha));
        b = second_half ?
                vec2i_vec2i_add(t1, vec2i_float_mult(vec2i_vec2i_sub(t2, t1), beta)) :
                vec2i_vec2i_add(t0, vec2i_float_mult(vec2i_vec2i_sub(t1, t0), beta));

        if (a.x > b.x) {
            temp = a;
            a = b;
            b = temp;
        }

        for (jndex = a.x; jndex <= b.x; jndex++) {
            set(map, jndex, t0.y + index, col);
        }
    }
}

void draw_line(pbitmap map, int x0, int y0, int x1, int y1, color_ptr col) {
    char steep = 0;
    int x, y, temp_1, temp_2, temp_x;
    float t;

    // Switch x and y around if dx < dy
    if (abs(x0 - x1) < abs(y0 - y1)) {
        temp_1 = x0;
        temp_2 = x1;
        x0 = y0;
        x1 = y1;
        y0 = temp_1;
        y1 = temp_2;

        steep = 1;
    }

    // swap if x0 > x1
    if (x0 > x1) {
        temp_x = x0;
        x0 = x1;
        x1 = temp_x;
    }

    for (x = 0; x < x1; x++) {
        t = (x - x0) / (float)(x1 - x0);
        y = (int) (y0 * (1.0f - t) + y1 * t);
        if (steep) {
            set(map, y, x, col);
        } else {
            set(map, x, y, col);
        }
    }
}