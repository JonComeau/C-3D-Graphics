#include <stdio.h>
#include "threedee/tga.h"

char unload_rle_data(pbitmap map, FILE *fp) {
//    const unsigned char max_chunk_length = 128;
//    unsigned long npixels = map->width * map->height;
//    unsigned long curpix = 0;
//    while (curpix < npixels) {
//        unsigned long chunkstart = curpix * map->bytes_pp;
//        unsigned long curbyte = curpix * map->bytes_pp;
//        unsigned char run_length = 1;
//        char raw = 1;
//        while (curpix + run_length < npixels && run_length < max_chunk_length) {
//            int succ_eq = 1;
//            for (int t = 0; succ_eq && t < map->bytes_pp; t++) {
//                succ_eq = (map->data[curbyte + t].value == map->data[curbyte + t + map->bytes_pp].value);
//            }
//            curbyte += map->bytes_pp;
//
//            if (1 == run_length)
//                raw = !succ_eq;
//            if (raw && succ_eq) {
//                run_length--;
//                break;
//            }
//            if (!raw && !succ_eq)
//                break;
//            run_length++;
//        }
//        curpix += run_length;
//        fputc(raw ? run_length - 1 : run_length + 127, fp);
//        if (!ferror(fp)) {
//            fprintf(stderr, "Can't dump the TGA file\n");
//            return 0;
//        }
//        fwrite((char*)(map->data + chunkstart), sizeof(char), (raw ? run_length * map->bytes_pp : map->bytes_pp), fp);
//        if (!ferror(fp)) {
//            fprintf(stderr, "Can't dump the TGA file\n");
//            return 0;
//        }
//    }
//    return 1;
}

int little_endianify (int number)
{
    return number % 256;
}

int big_endianify (int number)
{
    return number / 256;
}

void write_header (targa_header header, FILE *tga)
{
    fputc( header.id_length, tga );
    fputc( header.map_type, tga );
    fputc( header.image_type, tga );

    fputc( little_endianify(header.map_first), tga );
    fputc( big_endianify(header.map_first), tga );

    fputc( little_endianify(header.map_length), tga );
    fputc( big_endianify(header.map_length), tga );

    fputc( header.map_entry_size, tga );

    fputc( little_endianify(header.x), tga );
    fputc( big_endianify(header.x), tga );
    fputc( little_endianify(header.y), tga );
    fputc( big_endianify(header.y), tga );

    fputc( little_endianify(header.width), tga );
    fputc( big_endianify(header.width), tga );
    fputc( little_endianify(header.height), tga );
    fputc( big_endianify(header.height), tga );

    fputc( header.bits_per_pixel, tga );
    fputc( header.misc, tga );
}

void write_file(pbitmap map, char* filepath) {
    FILE *tga;
    targa_header header;
    int x, y;

    header.id_length = 0;
    header.map_type = 0;
    header.image_type = 2;     // uncompressed RGB image

    header.map_first = 0;
    header.map_length = 0;
    header.map_entry_size = 0;

    header.x = 0;
    header.y = 0;
    header.width = map->width;
    header.height = map->height;

    header.bits_per_pixel = 24;
    header.misc = 0x20;       // scan from upper left corner, wut dude

    // start to write file

    tga = fopen(filepath, "wb");

    write_header(header, tga);

    //// magic happens here -- write the pixels
    for (y = 0; y < map->height; ++y)
        for (x = 0; x < map->width; ++x)
        {
            color col = map->data[y * map->width + x];
            // B G R order
            fputc(col.rgba.b, tga);
            fputc(col.rgba.g, tga);
            fputc(col.rgba.r, tga);
        }

    //// magic ends here

    fclose(tga);
}