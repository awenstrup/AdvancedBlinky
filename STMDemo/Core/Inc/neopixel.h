#ifndef _NEOPIXEL_H

// INCLUDES ************
#include "stm32f1xx_hal.h"
#include <stdint.h>
#include <stdlib.h>

// DEFINES **************
// PWM lengths for high and low data bits
#define PWM_HI 38
#define PWM_LO 19

// Bytes per LED
#define NEO_PIXEL_MSG_SIZE_BYTES 3  // 3 bytes (1 byte for r, g, and b)

// STRUCTS *************
struct {
    uint8_t r, g, b;  // Use uint8_t to fit the 8 bit values
} typedef Color_t;

struct {
    uint8_t *buffer;
    size_t buffer_size;
    int num_pixels;
    size_t buffer_index;
} typedef Neopixel_t;

// VARIABLES ***********
extern TIM_HandleTypeDef htim2;
extern DMA_HandleTypeDef hdma_tim2_ch1;

// FUNCTIONS ***********
Neopixel_t *neo_initialize_strip(int num_leds);
int neo_set_pixel(Neopixel_t *neo, int pixel_id, Color_t color);
void free_neopixel(Neopixel_t *neo);
void led_render(Neopixel_t *neo);

#endif
