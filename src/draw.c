#include <stdlib.h>
#include "threedee/draw.h"
#include "threedee/matrix.h"

matrix_4x4 model_view;
matrix_4x4 viewport;
matrix_4x4 projection;

void set_viewport(int x, int y, int w, int h) {
    mat_identity_4x4(viewport);
    viewport[0][3] = x + w / 2.f;
    viewport[1][3] = y + h / 2.f;
    viewport[2][3] = 1.f;
    viewport[0][0] = w / 2.f;
    viewport[1][1] = h / 2.f;
    viewport[2][2] = 0;
}

void set_projection(float coeff) {
    mat_identity_4x4(projection);
    projection[3][2] = coeff;
}

void lookat(vec3f_ptr eye, vec3f_ptr center, vec3f_ptr up) {
    vec3f_ptr x, y, z;
    matrix_4x4 minv, tr;
    z = vec3f_normalize(vec3f_vec3f_sub(eye, center));
    x = vec3f_normalize(vec3f_vec3f_cross(up, z));
    y = vec3f_normalize(vec3f_vec3f_cross(z, x));
    mat_identity_4x4(minv);
    mat_identity_4x4(tr);

    minv[0][0] = x->x;
    minv[1][0] = y->x;
    minv[2][0] = z->x;

    minv[0][1] = x->y;
    minv[1][1] = y->y;
    minv[2][1] = z->y;

    minv[0][2] = x->z;
    minv[1][2] = y->z;
    minv[2][2] = z->z;

    mat_mul_4x4_4x4(minv, tr, model_view);
}

vec3f_ptr barycentric(vec2f_ptr a, vec2f_ptr b, vec2f_ptr c, vec2f_ptr p) {
    vec3f s[2];
    vec3f u;
    static vec3f ret;

    s[1].x = c->y - a->y;
    s[1].y = b->y - a->y;
    s[1].z = a->y - p->y;

    s[0].x = c->x - a->x;
    s[0].y = b->x - a->x;
    s[0].z = a->x - p->x;

    u = *vec3f_vec3f_cross(&s[0], &s[1]);
    if (abs((int) u.z) > 1e-2) {
        ret.x = 1.f - (u.x + u.y) / u.z;
        ret.y = u.y - u.z;
        ret.z = u.x / u.z;
    } else {
        ret.x = -1;
        ret.y = 1;
        ret.z = 1;
    }

    return &ret;
}

void line(pbitmap bitmap, int x0, int y0, int x1, int y1, color_ptr color) {
    char steep;
    int temp, x, y;
    float t;

    steep = 0;

    if (abs(x0 - x1) < abs(y0 - y1)) {
        temp = x0;
        x0 = y0;
        y0 = temp;

        temp = x1;
        x1 = y1;
        y1 = temp;

        steep = 1;
    }
    if (x0 > x1) {
        temp = x0;
        x0 = x1;
        x1 = temp;

        temp = y0;
        y0 = y1;
        y1 = temp;
    }

    for (x = x0; x <= x1; x++) {
        t = (x - x0)/(float)(x1-x0);
        y = (int) (y0 * (1. - t) + (y1 * t));
        if (steep)
            set(bitmap, y, x, color);
        else
            set(bitmap, x, y, color);
    }
}