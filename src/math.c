//
// Created by vylly on 6/11/2020.
//

#include "threedee/math.h"

vec3f barycentric(vec3f a, vec3f b, vec3f c, vec3f p) {
    vec3f v0, v1, v2;
    float d00, d01, d11, d20, d21, denom;

    v0 = vec3f_vec3f_sub(b, a);
    v1 = vec3f_vec3f_sub(c, a);
    v2 = vec3f_vec3f_sub(p, a);

    d00 = vec3f_vec3f_dot(v0, v0);
    d01 = vec3f_vec3f_dot(v0, v1);
    d11 = vec3f_vec3f_dot(v1, v1);
    d20 = vec3f_vec3f_dot(v2, v0);
    d21 = vec3f_vec3f_dot(v2, v1);

    denom = d00 * d11 - d01 * d01;

    return (vec3f){
        (d11 * d20 - d01 * d21) / denom,
        (d00 * d21 - d01 * d20) / denom,
        1.0f - ((d11 * d20 - d01 * d21) / denom) - ((d00 * d21 - d01 * d20) / denom)
    };
}