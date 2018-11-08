#include <stdio.h>
#include <stdlib.h>
#include "threedee/types.h"

/*
 * v  0.0  0.0  0.0
 * v  0.0  0.0  1.0
 * v  0.0  1.0  0.0
 * v  0.0  1.0  1.0
 * v  1.0  0.0  0.0
 * v  1.0  0.0  1.0
 * v  1.0  1.0  0.0
 * v  1.0  1.0  1.0
 *
 * g cube
 *
 * f  1  7  5
 * f  1  3  7
 * f  1  4  3
 * f  1  2  4
 * f  3  8  7
 * f  3  4  8
 * f  5  7  8
 * f  5  8  6
 * f  1  5  6
 * f  1  6  2
 * f  2  6  8
 * f  2  8  4
 */

void set_object(object_ptr obj);

int main(void) {
    object obj;

    printf("Set up cube\n");
    set_object(&obj);

    return 0;
}

void set_object(object_ptr obj) {
    int index;

    printf("Allocate space for verts\n");
    obj->vert_count = 8;
    obj->verts = malloc(obj->vert_count * sizeof(vert));
    if (!obj->verts) {
        fprintf(stderr, "Verts could not be allocated\n");
        return;
    }

    printf("\nStart setting vertices\n");
    obj->verts[0].x = 0.0f; obj->verts[0].y = 0.0f; obj->verts[0].z = 0.0f;
    obj->verts[1].x = 0.0f; obj->verts[1].y = 0.0f; obj->verts[1].z = 1.0f;
    obj->verts[2].x = 0.0f; obj->verts[2].y = 1.0f; obj->verts[2].z = 0.0f;
    obj->verts[3].x = 0.0f; obj->verts[3].y = 1.0f; obj->verts[3].z = 1.0f;
    obj->verts[4].x = 1.0f; obj->verts[4].y = 0.0f; obj->verts[4].z = 0.0f;
    obj->verts[5].x = 1.0f; obj->verts[5].y = 0.0f; obj->verts[5].z = 1.0f;
    obj->verts[6].x = 1.0f; obj->verts[6].y = 1.0f; obj->verts[6].z = 0.0f;
    obj->verts[7].x = 1.0f; obj->verts[7].y = 1.0f; obj->verts[7].z = 1.0f;

    for (index = 0; index < obj->vert_count; index++) {
        printf("\tv %4.2f %4.2f %4.2f\n",
               obj->verts[index].x,
               obj->verts[index].y,
               obj->verts[index].z);
    }

    printf("\nAllocate space for faces\n");
    obj->face_count = 12;
    obj->faces = malloc(obj->face_count * sizeof(face));
    if (!obj->faces) {
        fprintf(stderr, "Faces could not be allocated\n");
        return;
    }

    printf("Start setting faces\n");
    obj->faces[0].ind1 =  1; obj->faces[0].ind2 =  7; obj->faces[0].ind3 =  5;
    obj->faces[1].ind1 =  1; obj->faces[1].ind2 =  3; obj->faces[1].ind3 =  7;
    obj->faces[2].ind1 =  1; obj->faces[2].ind2 =  4; obj->faces[2].ind3 =  3;
    obj->faces[3].ind1 =  1; obj->faces[3].ind2 =  2; obj->faces[3].ind3 =  4;
    obj->faces[4].ind1 =  3; obj->faces[4].ind2 =  8; obj->faces[4].ind3 =  7;
    obj->faces[5].ind1 =  3; obj->faces[5].ind2 =  4; obj->faces[5].ind3 =  8;
    obj->faces[6].ind1 =  5; obj->faces[6].ind2 =  7; obj->faces[6].ind3 =  8;
    obj->faces[7].ind1 =  5; obj->faces[7].ind2 =  8; obj->faces[7].ind3 =  6;
    obj->faces[8].ind1 =  1; obj->faces[8].ind2 =  5; obj->faces[8].ind3 =  6;
    obj->faces[9].ind1 =  1; obj->faces[9].ind2 =  6; obj->faces[9].ind3 =  2;
    obj->faces[10].ind1 = 2; obj->faces[10].ind2 = 6; obj->faces[10].ind3 = 8;
    obj->faces[11].ind1 = 2; obj->faces[11].ind2 = 8; obj->faces[11].ind3 = 4;

    for (index = 0; index < obj->face_count; index++) {
        printf("\tf %i %i %i\n",
               obj->faces[index].ind1,
               obj->faces[index].ind2,
               obj->faces[index].ind3);
    }

    printf("\nTest vertex from face\n");
    for (index = 0; index < obj->face_count; index++) {
        printf("index: %i\n", index);
        printf("\t%i:\tv %.2f %.2f %.2f\n",
               obj->faces[index].ind1,
               obj->verts[obj->faces[index].ind1-1].x,
               obj->verts[obj->faces[index].ind1-1].y,
               obj->verts[obj->faces[index].ind1-1].z);
        printf("\t%i:\tv %.2f %.2f %.2f\n",
               obj->faces[index].ind2,
               obj->verts[obj->faces[index].ind2-1].x,
               obj->verts[obj->faces[index].ind2-1].y,
               obj->verts[obj->faces[index].ind2-1].z);
        printf("\t%i:\tv %.2f %.2f %.2f\n",
               obj->faces[index].ind3,
               obj->verts[obj->faces[index].ind3-1].x,
               obj->verts[obj->faces[index].ind3-1].y,
               obj->verts[obj->faces[index].ind3-1].z);
    }
}