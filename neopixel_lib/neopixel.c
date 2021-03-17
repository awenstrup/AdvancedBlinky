#include <stdlib.h>

#include "neopixel.h"

/**
 * @brief Initializes the memory needed for the neopixel strip buffer
 * @return Pointer to a new Neopixel_t object, NULL if errored
 */
Neopixel_t *neo_initialize_strip(int num_leds) {
    Neopixel_t *neo = malloc(sizeof(Neopixel_t));

    // Check that malloc is successful
    if (neo == NULL) {
        return NULL;
    }

    neo->num_pixels = num_leds;
    neo->buffer_size = num_leds * NEO_PIXEL_MSG_SIZE_BYTES;
    neo->buffer = malloc(neo->buffer_size * sizeof(char));

    // Check that malloc is successful
    if (neo->buffer == NULL) {
        return NULL;
    }

    // Clear neo_buffer
    for (size_t i = 0; i < neo->buffer_size; i++) {
        neo->buffer[neo->buffer_size] = 0;
    }

    return neo;
}

/**
 * @brief Sets one pixel of the strip to a color_t value
 * @return 0 if successful, -1 if unsuccessful
 */
int neo_set_pixel(Neopixel_t *neo, int pixel_id, Color_t color) {
    if (pixel_id >= neo->num_pixels) {
        return -1;
    }

    size_t start_index = pixel_id * NEO_PIXEL_MSG_SIZE_BYTES;
    neo->buffer[start_index] = color.r;
    neo->buffer[start_index + 1] = color.g;
    neo->buffer[start_index + 2] = color.b;
    
    return 0;
}

/**
 * @brief Destructs a Neopixel_t object
 */
void free_neopixel(Neopixel_t *neo) {
    free(neo->buffer);
    free(neo);
}

