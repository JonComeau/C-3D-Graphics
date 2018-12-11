#include <math.h>
#include "threedee/s_t_r.h"

void rotate_object();

void build_look_up_tables(void) {
    int angle;
    float rad;

    for (angle = 0; angle <= 360; angle++) {
        rad = (3.14159f * (float)angle / 180.0f);

        cos_look[angle] = cosf(rad);
        sin_look[angle] = sinf(rad);
    }
}