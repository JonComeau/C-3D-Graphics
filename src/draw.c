#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <stdio.h>
#include <threedee/ops.h>
#include <threedee/math.h>
#include "threedee/draw.h"

//void draw_tri(pbitmap map, int* zbuffer, vec2i t0, vec2i t1, vec2i t2, color_ptr col) {
//    vec2i temp, a, b;
//    int total_height, index, jndex, seg_height;
//    char second_half;
//    float alpha, beta;
//
//    if (t0.y > t1.y) {
//        temp = t0;
//        t0 = t1;
//        t1 = temp;
//    }
//
//    if (t0.y > t1.y) {
//        temp = t0;
//        t0 = t2;
//        t2 = temp;
//    }
//
//    if (t1.y > t2.y) {
//        temp = t1;
//        t1 = t2;
//        t2 = temp;
//    }
//
//    total_height = t2.y - t0.y;
//
//    for (index = 0; index < total_height; index++) {
//        second_half = index > t1.y - t0.y || t1.y == t0.y;
//        seg_height = second_half ? t2.y - t1.y : t1.y - t0.y;
//        alpha = (float) index / total_height;
//        beta = (float) (index - (second_half ? t1.y - t0.y : 0)) / seg_height;
//        a = vec2i_vec2i_add(t0, vec2i_float_mult(vec2i_vec2i_sub(t2, t0), alpha));
//        b = second_half ?
//            vec2i_vec2i_add(t1, vec2i_float_mult(vec2i_vec2i_sub(t2, t1), beta)) :
//            vec2i_vec2i_add(t0, vec2i_float_mult(vec2i_vec2i_sub(t1, t0), beta));
//
//        if (a.x > b.x) {
//            temp = a;
//            a = b;
//            b = temp;
//        }
//
//        for (jndex = a.x; jndex <= b.x; jndex++) {
//            set(map, jndex, t0.y + index, col);
//        }
//    }
//}

void draw_tri(pbitmap map, float* zbuffer, vec3f t0, vec3f t1, vec3f t2, color_ptr col) {
    vec3f p, bc_screen;
    vec2f bboxmin, bboxmax, clamp;

    bboxmin = (vec2f){FLT_MAX, FLT_MAX};
    bboxmax = (vec2f){-FLT_MAX, -FLT_MAX};
    clamp = (vec2f){map->width - 1., map->height - 1};

    bboxmin.x = max(0.f, min(bboxmin.x, t0.x));
    bboxmin.x = max(0.f, min(bboxmin.x, t1.x));
    bboxmin.x = max(0.f, min(bboxmin.x, t2.x));
    bboxmin.y = max(0.f, min(bboxmin.y, t0.y));
    bboxmin.y = max(0.f, min(bboxmin.y, t1.y));
    bboxmin.y = max(0.f, min(bboxmin.y, t2.y));

    bboxmax.x = min(clamp.x, max(bboxmax.x, t0.x));
    bboxmax.x = min(clamp.x, max(bboxmax.x, t1.x));
    bboxmax.x = min(clamp.x, max(bboxmax.x, t2.x));
    bboxmax.y = min(clamp.y, max(bboxmax.y, t0.y));
    bboxmax.y = min(clamp.y, max(bboxmax.y, t1.y));
    bboxmax.y = min(clamp.y, max(bboxmax.y, t2.y));

    p = (vec3f){0, 0, 0};

    for (p.x = bboxmin.x; p.x <= bboxmax.x; p.x++) {
        for (p.y = bboxmin.y; p.y <= bboxmax.y; p.y++) {
            bc_screen = barycentric(t0, t1, t2, p);

            if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0)
                continue;

            p.z += t0.z * bc_screen.array[0];
            p.z += t1.z * bc_screen.array[1];
            p.z += t2.z * bc_screen.array[2];

            if (zbuffer[(int)(p.x + p.y * map->width)] < p.z) {
                zbuffer[(int)(p.x + p.y * map->width)] = p.z;
                set(map, p.x, p.y, col);
            }
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