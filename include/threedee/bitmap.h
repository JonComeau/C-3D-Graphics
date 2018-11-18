#ifndef THREEDEE_BITMAP_H
#define THREEDEE_BITMAP_H

typedef union color_typ {
    struct {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    } rgba;
    unsigned char raw[4];
    unsigned int value;
} color, *color_ptr;

typedef struct bitmap_typ {
    int width;
    int height;
    int bytes_pp;
    color *data;
} bitmap, *pbitmap;

int create_bitmap(pbitmap self, int width, int height, int bytes_pp);
char set(pbitmap self, int x, int y, color_ptr color);
char flip_vert(pbitmap self);

#endif //THREEDEE_BITMAP_H
