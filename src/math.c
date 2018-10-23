//#include <math.h>
//#include "threedee/types.h"
//#include "threedee/math.h"
//
//// This function creates a vector from two points in 3D space
//void make_vector_3d(point_3d_ptr init, point_3d_ptr term, vector_3d_ptr result) {
//    result->x = term->x - init->x;
//    result->y = term->y - init->y;
//    result->z = term->z - init->z;
//}
//
//// computes the magnitude of a vector
//float vector_mag_3d(vector_3d_ptr v) {
//    return ((float)sqrt(v->x*v->x + v->y*v->y + v->z*v->z));
//}
//
//// this function computes the dot product of two vectors
//float dot_product_3d(vector_3d_ptr u, vector_3d_ptr v) {
//    return ((u->x*v->x) + (u->y*v->y) + (u->z*v->z));
//}
//
//// this functions computes the cross product between two vectors
//void cross_product_3d(vector_3d_ptr u, vector_3d_ptr v, vector_3d_ptr normal) {
//    normal->x =  (u->y*v->z - u->z*v->y);
//    normal->y = -(u->x*v->z - u->z*v->x);
//    normal->z =  (u->x*v->y - u->y*v->x);
//}
//
