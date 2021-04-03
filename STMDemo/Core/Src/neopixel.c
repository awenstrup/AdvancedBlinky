#include "neopixel.h"
#include "stm32f1xx_hal.h"
#include <stdint.h>
#include <stdlib.h>

extern TIM_HandleTypeDef htim2;
extern DMA_HandleTypeDef hdma_tim2_ch1;

uint8_t wr_buf[48]; // 2 neopixel's worth of data TODO get rid of all magic numbers
uint_fast8_t index = 0; // keep track of the next Neopixel to write to the DMA buffer

Neopixel_t *neopixel;
/* 
For now, create a single neopixel and force the name "neopixel"
In theory, we should have an array or list of these so we can have
abritrarily many, but idk how much computation overhead that'll add
or if we'll be able to realistically run more than one, so we just
create one for now. In a perfect world, we could do this:

n1 = neo_initialize_strip(5)  // creates Neopixel_t and adds it to list
n2 = neo_initialize_strip(6)  // create another one
...

but instead, we write this:

n1 = neo_initialize_strip(5)  // only one allowed

*/

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
    neo->buffer = malloc(neo->buffer_size * sizeof(uint8_t));

    // Check that malloc is successful
    if (neo->buffer == NULL) {
        return NULL;
    }

    // Clear neo_buffer
    for (size_t i = 0; i < neo->buffer_size; i++) {
        neo->buffer[neo->buffer_size] = 0;
    }

    neopixel = &neo;
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
 * @brief Display the data in a Neopixel_t object on hardware
 * 
 * Convert RGB data into PWM format and store in a DMA buffer
 */ 
void led_render() {
  if (index != 0 || hdma_tim2_ch1.State != HAL_DMA_STATE_READY) {
      // Ongoing transfer, cancel!
      for (uint8_t i = 0; i < (neopixel->num_pixels * NEO_PIXEL_MSG_SIZE_BYTES); i++) {
          wr_buf[i] = 0;
      } 
      index = 0;
      HAL_TIM_PWM_Stop_DMA(&htim2, TIM_CHANNEL_1);
      return;
  }
  
  // Fill the buffer
  for (uint8_t i = 0; i < 48; i++) {
      wr_buf[i] = (neopixel->buffer[i/8] & (1 << (i%8))) ? PWM_HI : PWM_LO;
  }

  HAL_TIM_PWM_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t *)wr_buf, 48);
  index = 2; // Since we're ready for the next buffer
}

/**
 * @brief IRQ to keep the DMA buffer full of the lastest information
 * 
 * TODO this is only half done, figure out how to get NeoPixel data
 * in here.
 */
void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim) {
    int num_pixels = neopixel->num_pixels;
    if (index < num_pixels) {
        for(uint_fast8_t i = 0; i < 24; i++) {
            wr_buf[i] = (neopixel->buffer[(i/8) + (index*NEO_PIXEL_MSG_SIZE_BYTES)] & (1 << (i%8))) ? PWM_HI : PWM_LO;
        }
        index++;
    } else if (index < num_pixels + 2) {
        // 1.25 us per bit * 24 bits per pixel = 30 us per pixel.
        // 2 pixels or 60 us is enough to reset
        for (uint8_t i = 0; i < 48 / 2; i++) {
            wr_buf[i] = 0;
        } 
        index++;
    }
}

/**
 * @brief IRQ to keep the DMA buffer full of the lastest information
 * 
 * Same as above, but fills the second half of the buffer (for odd indexed
 * neopixels) instead of the first half of the buffer
 */
void HAL_TIM_PWM_PulseFinishedHalfCpltCallback(TIM_HandleTypeDef *htim) {
    int num_pixels = neopixel->num_pixels;
    if (index < num_pixels) {
        for(uint_fast8_t i = 24; i < 48; i++) {
            wr_buf[i] = (neopixel->buffer[(i/8) + (index*NEO_PIXEL_MSG_SIZE_BYTES)] & (1 << (i%8))) ? PWM_HI : PWM_LO;
        }
        index++;
    } else if (index < num_pixels + 2) {
        // 1.25 us per bit * 24 bits per pixel = 30 us per pixel.
        // 2 pixels or 60 us is enough to reset
        for (uint8_t i = 0; i < 48 / 2; i++) {
            wr_buf[i] = 0;
        } 
        index++;
    }
    else {
        // Sending complete, stop until next led_render call
        index = 0;
        HAL_TIM_PWM_Stop_DMA(&htim2, TIM_CHANNEL_1);
    } 
}