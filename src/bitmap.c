#include <stdlib.h>
#include "threedee/bitmap.h"

int create_bitmap(pbitmap self, int width, int height, int bpp) {
    self->height = height;
    self->width = width;
    self->bpp = bpp;

    self->data = calloc(width * height, sizeof(rgba));

    return (self->data) ? 1 : 0;
}