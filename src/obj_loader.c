//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <threedee/math.h>
//#include <math.h>
//#include "threedee/types.h"
//#include "threedee/obj_loader.h"
//
//// This function gets a line from a PLG file and strips comments
//char *plg_get_line(char *string, int max_length, FILE *fp) {
//    char buffer[80];
//    int length, index = 0, index_2 = 0, parsed = 0;
//
//    while (1) {
//        if (!fgets(buffer, max_length, fp)) return(NULL);
//
//        length = strlen(buffer);
//        while (buffer[index - 1] == ' ') index++;
//
//        parsed = 0;
//        index_2 = 0;
//
//        while (!parsed) {
//            if (buffer[index] != '#' && buffer[index] != ';') {
//                string[index_2] = buffer[index];
//
//                if (string[index_2] == 0) parsed = 1;
//
//                index++;
//                index_2++;
//            } else {
//                string[index_2] = 0;
//                parsed = 1;
//            }
//
//            if (strlen(string)) return string;
//        }
//    }
//}
//
//int plg_load_object(object_ptr the_object, char *filename, float scale) {
//    FILE *fp;
//    static int id_number = 0;
//    char buffer[80], object_name[32], *token;
//    unsigned int total_vertices, total_polys, num_vertices, color_des, logical_color, shading, index, index_2,
//                 vertex_num, vertex_0, vertex_1, vertex_2;
//    float x, y, z;
//    vector_3d u, v, normal;
//
//    // open the file
//    if ((fp=fopen(filename, "r")) == NULL) {
//        printf("\nCouldn't open file %s", filename);
//        return 0;
//    }
//
//    // First is the header line
//    if (!plg_get_line(buffer, 80, fp)) {
//        printf("\nError with PLG file %s", filename);
//        fclose(fp);
//        return 0;
//    }
//
//    // Extract object name and number of vertices and polygons
//    sscanf(buffer, "%s %d %d", object_name, &total_vertices, &total_polys);
//
//    the_object->num_vertices = total_vertices;
//    the_object->num_polys = total_polys;
//    the_object->state = 1;
//    the_object->id = id_number++;
//
//    for (index = 0; index < total_vertices; index++) {
//        if (!plg_get_line(buffer, 80, fp)) {
//            printf("\nError with PLG file %s", filename);
//            fclose(fp);
//            return 0;
//        }
//
//        sscanf(buffer, "%f %f %f", &x, &y, &z);
//
//        the_object->vertices_local[index].x = x*scale;
//        the_object->vertices_local[index].y = y*scale;
//        the_object->vertices_local[index].z = z*scale;
//
//        // init token getter and get first token; color descriptor
//        if (!(token = strtok(buffer, " "))) {
//            printf("\nError with PLG file %s", filename);
//            fclose(fp);
//            return 0;
//        }
//
//        // test if the number is hexadecimal
//        if (token[0] == '0' && (token[1] == 'x' || token[1] == 'X')) sscanf(&token[2], "%x", &color_des);
//        else color_des = atoi(token);
//
//        // Extract base color and type of shading
//        logical_color = color_des & 0x00ff;
//        shading = color_des >> 12;
//
//        // read number of vertices in polygon
//        if (!(token = strtok(NULL, " "))) {
//            printf("\nError with PLG file %s", filename);
//            fclose(fp);
//            return 0;
//        }
//
//        if ((num_vertices = atoi(token)) <= 0) {
//            printf("\nError with PLG file (number of vertices) %s", filename);
//            fclose(fp);
//            return 0;
//        }
//
//        the_object->polys[index].num_points = num_vertices;
//        the_object->polys[index].color = logical_color;
//        the_object->polys[index].shading = shading;
//        the_object->polys[index].two_sided = 0;
//        the_object->polys[index].visible = 1;
//        the_object->polys[index].clipped = 0;
//        the_object->polys[index].active = 1;
//
//        // Read in the Polygon Vertex list
//        for (index_2 = 0; index_2 < num_vertices; index_2++) {
//            if (!(token = strtok(NULL, " "))) {
//                printf("\nError with PLF file %s", filename);
//                fclose(fp);
//                return 0;
//            }
//
//            vertex_num = atoi(token);
//
//            the_object->polys[index].vertex_list[index_2] = vertex_num;
//        }
//
//        vertex_0 = the_object->polys[index].vertex_list[0];
//        vertex_1 = the_object->polys[index].vertex_list[1];
//        vertex_2 = the_object->polys[index].vertex_list[2];
//
//        make_vector_3d(&the_object->vertices_local[vertex_0], &the_object->vertices_local[vertex_1], &u);
//        make_vector_3d(&the_object->vertices_local[vertex_0], &the_object->vertices_local[vertex_2], &v);
//        cross_product_3d(&v, &u, &normal);
//
//        the_object->polys[index].normal_length = vector_mag_3d(&normal);
//    }
//
//    fclose(fp);
//
//    compute_object_radius(the_object);
//
//    return 1;
//}
//
//float compute_object_radius(object_ptr the_object) {
//    float new_radius, // Used in average radius calculation of object
//        x, y, z; // A single vertex
//    int index;
//
//    // Reset the Object's radius
//    the_object->radius = 0;
//
//    for (index = 0; index < the_object->num_vertices; index++) {
//        x = the_object->vertices_local[index].x;
//        y = the_object->vertices_local[index].y;
//        z = the_object->vertices_local[index].z;
//
//        new_radius = sqrtf(x*x + y*y + z*z);
//
//        // is this radius bigger than last?
//        if (new_radius > the_object->radius) the_object->radius = new_radius;
//    }
//
//    return the_object->radius;
//}