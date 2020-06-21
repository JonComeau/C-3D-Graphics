//
// Created by vylly on 6/11/2020.
//

#include <math.h>
#include "threedee/math.h"

vec3f barycentric(vec3f a, vec3f b, vec3f c, vec3f p) {
    vec3f s[2], u;
    int i;

    for (i = 2; i--;) {
        s[i].array[0] = c.array[i]-a.array[i];
        s[i].array[1] = b.array[i]-a.array[i];
        s[i].array[2] = a.array[i]-p.array[i];
    }

    u = vec3f_vec3f_cross(s[0], s[1]);
    if (fabsf(u.array[2]) > 1e-2) {
        return (vec3f) {
            1.f - (u.x + u.y) / u.z,
            u.y / u.z,
            u.x / u.z
        };
    }
    return (vec3f) {-1,1,1};
}