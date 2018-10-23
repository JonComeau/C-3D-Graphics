#include <stdlib.h>
#include "threedee/bitmap.h"

int create_bitmap(pbitmap self, int width, int height) {
    self->height = height;
    self->width = width;

    self->data = calloc(width * height, sizeof(rgba));

    return (self->data) ? 1 : 0;
}