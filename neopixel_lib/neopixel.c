#include <stdlib.h>

#include "neopixel.h"

int ticker = 0;

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
    neo->buffer_index = 0;

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

/**
 * @brief Callback function to call every 0.4 us
 * TODO this is just skeleton code; figure out includes and stuff
 */
void callback(Neopixel_t *neo, GPIO_TypeDef *port, uint16_t pin) {
    switch (ticker) {
        case 0:
            // set pin high
            HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
            ticker++;
            break;
        case 1:
            // set pin to data value
            int bit = (neo->buffer[neo->buffer_index/8] & (1 << (neo->buffer_index % 8)));
            HAL_GPIO_WritePin(port, pin, ((bit == 0) ? GPIO_PIN_RESET : GPIO_PIN_SET));
            ticker++;
            break;
        case 2:
            // set pin low
            HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
            ticker = 0;
            break;
    }
}

