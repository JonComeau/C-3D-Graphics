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

typedef union vec2i_typ {
    struct {
        int x, y;
    };
    int array[2];
} vec2i, *vec2i_ptr;

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

// Vec3f
float vec3f_norm(vec3f self);
vec3f vec3f_normalize(vec3f self);
vec3f vec3f_normalize_l(vec3f self, float l);
float vec3f_vec3f_mult(vec3f lhs, vec3f rhs);
vec3f vec3f_vec3f_add(vec3f lhs, vec3f rhs);
vec3f vec3f_vec3f_sub(vec3f lhs, vec3f rhs);
vec3f vec3f_vec3f_cross(vec3f lhs, vec3f rhs);
vec3f vec3f_float_mult(vec3f lhs, float scalar);
float vec3f_vec3f_dot(vec3f lhs, vec3f rhs);

vec3f mat4x4_vec3f_mult(mat4x4 mat, vec3f vec);

// Vec2i
vec2i vec2i_vec2i_add(vec2i lhs, vec2i rhs);
vec2i vec2i_vec2i_sub(vec2i lhs, vec2i rhs);
vec2i vec2i_float_mult(vec2i self, float scalar);

void print_obj(object obj);

#endif //THREEDEE_TYPES_H