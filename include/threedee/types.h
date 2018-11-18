#ifndef THREEDEE_TYPES_H
#define THREEDEE_TYPES_H

typedef float matrix_4x4[4][4];

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

typedef union face_type {
    // The vertices that make up face. Only triangles allowed.
    struct {
        int ind1, ind2, ind3;
    };
    int array[3];
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

vec3f_ptr vec3f_normalize(vec3f_ptr self);
vec3f_ptr vec3f_normalize_l(vec3f_ptr self, float l);
float vec3f_vec3f_mult(vec3f_ptr lhs, vec3f_ptr rhs);
vec3f_ptr vec3f_vec3f_add(vec3f_ptr lhs, vec3f_ptr rhs);
vec3f_ptr vec3f_vec3f_sub(vec3f_ptr lhs, vec3f_ptr rhs);
vec3f_ptr vec3f_vec3f_cross(vec3f_ptr lhs, vec3f_ptr rhs);

vec3f_ptr vec3f_float_mult(vec3f_ptr lhs, float scalar);

#endif //THREEDEE_TYPES_H