#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include <stdlib.h>

#define NEO_PIXEL_MSG_SIZE_BYTES 3  // 3 bytes (1 byte for r, g, and b)

struct {
    uint8_t r, g, b;  // Use char to fit the 8 bit values
} typedef Color_t;

struct {
    uint8_t *buffer;
    size_t buffer_size;
    int num_pixels;
    size_t buffer_index;
} typedef Neopixel_t;

int ticker;

Neopixel_t *neo_initialize_strip(int num_leds);
int neo_set_pixel(Neopixel_t *neo, int pixel_id, Color_t color);
void free_neopixel(Neopixel_t *neo);
void callback(Neopixel_t *neo, int pin);

#endif
