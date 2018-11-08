#include <math.h>
#include <stddef.h>
#include "threedee/types.h"

inline float vec3f_norm(vec3f_ptr self) {
    return sqrtf(self->x*self->x+self->y*self->y+self->z*self->z);
}

inline vec3f_ptr vec3f_normalize(vec3f_ptr self, float l) {
    return vec3f_float_mult(self, l / vec3f_norm(self));
}

inline float vec3f_vec3f_mult(vec3f_ptr lhs, vec3f_ptr rhs) {
    return lhs->x*rhs->x + lhs->y*rhs->y + lhs->z*rhs->z;
}

vec3f_ptr vec3f_vec3f_add(vec3f_ptr lhs, vec3f_ptr rhs) {

}

vec3f_ptr vec3f_vec3f_sub(vec3f_ptr lhs, vec3f_ptr rhs);