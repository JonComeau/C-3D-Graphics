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

void lookat(vec3f eye, vec3f center, vec3f up) {
    vec3f x, y, z;
    matrix_4x4 minv, tr;
    z = vec3f_normalize(vec3f_sub(eye, center));
}