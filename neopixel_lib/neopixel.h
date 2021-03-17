#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include <stdlib.h>

#define NEO_PIXEL_MSG_SIZE_BYTES 3  // 3 bytes (1 byte for r, g, and b)

struct {
    unsigned char r, g, b;  // Use char to fit the 8 bit values
} typedef Color_t;

struct {
    unsigned char *buffer;
    size_t buffer_size;
    int num_pixels;
} typedef Neopixel_t;

Neopixel_t *neo_initialize_strip(int num_leds);
int neo_set_pixel(Neopixel_t *neo, int pixel_id, Color_t color);
void free_neopixel(Neopixel_t *neo);

#endif
