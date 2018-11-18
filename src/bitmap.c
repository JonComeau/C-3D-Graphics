#include <stdlib.h>
#include <stdio.h>
#include <mem.h>
#include "threedee/bitmap.h"

int create_bitmap(pbitmap self, int width, int height, int bytes_pp) {
    int index;

    self->height = height;
    self->width = width;
    self->bytes_pp = bytes_pp;

    self->data = calloc(width * height, sizeof(color));

    for (index = 0; index < width * height; index++) {
        self->data[index].rgba.a = 255;
        if (index < 50)
            printf("r: %i, g: %i, b: %i, a:%i\n",
                   self->data[index].rgba.r,
                   self->data[index].rgba.g,
                   self->data[index].rgba.b,
                   self->data[index].rgba.a);
    }

    return (self->data) ? 1 : 0;
}

char set(pbitmap self, int x, int y, color_ptr color) {
    if (!self->data || x < 0 || y < 0 || x >= self->width || y >= self->height)
        return 0;
    memcpy(self->data + (x + y * self->width), color->raw, self->bytes_pp);
    return 1;
}

char flip_vert(pbitmap self) {
    unsigned long bytes_per_line, l1, l2;
    unsigned char *line;
    int half, index;

    if (!self->data) return 0;

    bytes_per_line = self->width * self->bytes_pp;
    line = calloc(bytes_per_line, sizeof(unsigned char));
    half = self->height >> 1;

    for (index = 0; index < half; index++) {
        l1 = index * bytes_per_line;
        l2 = (self->height - 1 - index) * bytes_per_line;
        memmove((void *)line,            (void *)(self->data+l1), bytes_per_line);
        memmove((void *)(self->data+l1), (void *)(self->data+l2), bytes_per_line);
        memmove((void *)(self->data+l2), (void *)line,            bytes_per_line);
    }

    free(line);
    return 1;
}