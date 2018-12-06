#ifndef THREEDEE_TYPES_H
#define THREEDEE_TYPES_H

typedef struct mat4x4_typ {
    float m[4][4];
} mat4x4, *mat4x4_ptr;

typedef union vec4f_typ {
    float array[4];
} vec4f, *vec4f_ptr;

typedef union vec3f_typ {
    struct {
        float x, y, z;
    };
    float array[3];
} vec3f, *vec3f_ptr;

typedef union vec2f_typ {
    struct {
        float x, y;
    };
    float array[2];
} vec2f, *vec2f_ptr;

typedef struct face_type {
    int v[3];
} face, *face_ptr;

typedef struct object_typ {
    // This is the array of vertices
    vec3f_ptr verts;
    // The number of verts in object
    int vert_count;
    // This is an array of face_ptr
    face_ptr faces;
    // The number of faces in object
    int face_count;
} object, *object_ptr;

typedef struct tri_typ {
    vec3f p[3];
} tri, *tri_ptr;

float vec3f_norm(vec3f_ptr self);
vec3f_ptr vec3f_normalize(vec3f_ptr self);
vec3f_ptr vec3f_normalize_l(vec3f_ptr self, float l);
float vec3f_vec3f_mult(vec3f_ptr lhs, vec3f_ptr rhs);
vec3f_ptr vec3f_vec3f_add(vec3f_ptr lhs, vec3f_ptr rhs);
vec3f_ptr vec3f_vec3f_sub(vec3f_ptr lhs, vec3f_ptr rhs);
vec3f_ptr vec3f_vec3f_cross(vec3f_ptr lhs, vec3f_ptr rhs);
vec3f_ptr vec3f_float_mult(vec3f_ptr lhs, float scalar);

vec3f_ptr mat4x4_vec3f_mult(mat4x4_ptr mat, vec3f_ptr vec);

#endif //THREEDEE_TYPES_H