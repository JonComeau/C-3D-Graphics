#ifndef THREEDEE_BITMAP_H
#define THREEDEE_BITMAP_H

typedef struct rgba_typ {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} rgba;

typedef struct bitmap_typ {
    int width;
    int height;
    rgba *data;
} bitmap, *pbitmap;

int create_bitmap(pbitmap self, int width, int height);

#endif //THREEDEE_BITMAP_H
