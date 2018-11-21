#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "threedee/bitmap.h"

int create_bitmap(pbitmap self, int width, int height, int bytes_pp) {
    int index;

    self->height = height;
    self->width = width;
    self->bytes_pp = bytes_pp;

    self->data = calloc(width * height, sizeof(color));

    for (index = 0; index < width * height; index++) {
        self->data[index].rgba.a = 255;
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
    unsigned char *line;
    unsigned int half, index;

    if (!self->data) return 0;

    line = malloc(self->width * sizeof(color));
    half = self->height >> 1;

    for (index = 0; index < half; index++) {
        memmove(line,
                self->data + index * self->width,
                self->width * sizeof(color));
        memmove(self->data + index * self->width,
                self->data + (self->height - index - 1) * self->width,
                self->width * sizeof(color));
        memmove(self->data + (self->height - index - 1) * self->width,
                line,
                self->width * sizeof(color));
    }

    free(line);
    return 1;
}