//#ifndef THREEDEE_TYPES_H
//#define THREEDEE_TYPES_H
//
//typedef float matrix_4x4[4][4];
//typedef float matrix_1x4[4];
//
//typedef struct vector_3d_typ {
//    float x, y, z, w; // a 3D vector along with normalization factor if needed
//} point_3d, vector_3d, *point_3d_ptr, *vector_3d_ptr;
//
//typedef struct dir_3d_typ {
//    int ang_x, // angle relative to x-axis
//        ang_y, // angle relative to y-axis
//        ang_z; // angle relative to z-axis
//} dir_3d, *dir_3d_ptr;
//
//typedef struct polygon_typ {
//    int num_points; // number of points in polygon (usually 3 or 4)
//    int vertex_list[MAX_POINTS_PER_POLY]; // the index number of vertices
//    int color; // color of polygon
//    int shade; // the final shade of color after lighting
//    int shading; // type of lighting, flat or constant shading
//    int two_sided; // flags if the polygon is two-sided
//    int visible; // used to remove backfaces
//    int active; // used to turn faces on and off
//    int clipped; // flags that polygon has been clipped or removed
//    float normal_length; // pre-computed magnitude of normal
//} polygon, *polygon_ptr;
//
//typedef struct facet_typ {
//    int num_points; // number of vertices
//    int color; // color of polygon
//    int shade; // the final shade of color after lighting
//    int shading; // type of shading to use
//    int two_sided; // is the facet two-sided
//    int visible; // is th facet transparent
//    int clipped; // has this poly been clipped
//    int active; // used to turn faces on and off
//    point_3d vertex_list[MAX_POINTS_PER_POLY];
//    float normal_length;
//} facet, *facet_ptr;
//
//typedef struct object_typ {
//    int id; // identification number of object
//    int num_vertices; // total number of vertices in object
//    point_3d vertices_local[MAX_VERTICES_PER_OBJECT]; // local vertices
//    point_3d vertices_world[MAX_VERTICES_PER_OBJECT]; // world vertices
//    point_3d vertices_camera[MAX_VERTICES_PER_OBJECT]; // camera vertices
//    int num_polys; // the number of polygons in the object
//    polygon polys[MAX_POLYS_PER_OBJECT]; // the polygons of the object
//    float radius; // the average radius of the object
//    int state; // state of the object
//    point_3d world_pos; // position of the object in world coordinates
//} object, *object_ptr;
//
//#endif //THREEDEE_TYPES_H
