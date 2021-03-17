#include <stdio.h>

#include "minunit.h"
#include "neopixel.h"
#include "test_neopixel.h"

#define NUM_LEDS 5

void print_buffer(Neopixel_t *neo) {
    for(int i = 0; i < NUM_LEDS; i++) {
        size_t start_index = i * NEO_PIXEL_MSG_SIZE_BYTES;
        printf("Pixel %i\tR: %i\tG: %i\tB: %i\n", i, neo->buffer[start_index], neo->buffer[start_index + 1], neo->buffer[start_index + 2]); 
    }
}

int main() {
    Neopixel_t *neo = neo_initialize_strip(NUM_LEDS);
    size_t expected_len = NUM_LEDS * NEO_PIXEL_MSG_SIZE_BYTES;
    printf("Size of buffer: %lu, Expected: %lu\n", neo->buffer_size, expected_len);
    print_buffer(neo);

    int pixel_edit = 2;
    Color_t color = {100, 200, 250};
    printf("\nSetting pixel %i to (%i, %i, %i)\n", pixel_edit, color.r, color.g, color.b);
    neo_set_pixel(neo, pixel_edit, color);
    print_buffer(neo);

    return 0;
}
