#include <stdio.h>
#include "threedee/draw.h"

void draw_object_wire(object_ptr object) {
    int curr_poly, // the current polygon
        curr_vert, // The current vertex
        vert; // Vertex index
    float x1, x2, y1, y2, z1, z2; // Working vars
    int ix1, ix2, iy1, iy2; // ints used to hold screen

    for (curr_poly = 0; curr_poly < object->num_polys; curr_poly++) {
        // is the poly visible
        if (object->polys[curr_poly].visible == 0 ||
            object->polys[curr_poly].clipped)
            continue;

        printf("\nPolygon #%d", curr_poly);
        for (curr_vert = 0; curr_vert < object->polys[curr_poly].num_points - 1; curr_vert++) {
            // extract two endpoints
            vert = object->polys[curr_poly].vertex_list[curr_vert];

            x1 = object->vertices_camera[vert].x;
            y1 = object->vertices_camera[vert].y;
            z1 = object->vertices_camera[vert].z;

            vert = object->polys[curr_poly].vertex_list[curr_vert + 1];

            x2 = object->vertices_camera[vert].x;
            y2 = object->vertices_camera[vert].y;
            z2 = object->vertices_camera[vert].z;

            // convert coordinates
            //x1 = (HALF_SCREEN_WIDTH + x1 * viewing_distance / z1);
        }
    }
}