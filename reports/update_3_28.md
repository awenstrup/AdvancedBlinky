# Project Update: 3/28

## Project Goal

Our goal from the begining of the project has been to "develop a NeoPixel library that runs on STM32 microcontrollers." For context, a NeoPixel is an RGB LED sold by Adafruit, and comes in strips such that each light is can be controlled independently via a proprietary digital signal. We knew that this development goal would help us satisfy our learning goals of becoming familiar with STM32 development, learning about embedded buildchains, and getting more practice debugging embedded code, and we have achieved all of those learning goals by this point in the project.

## Summary of work

We have made a lot of progress on our project, and been frustratingly close to our MVP for a while. Check out our trello [here](https://trello.com/b/4Y54vG8e/advancedblinky) for an overview of what we've done. 

Our development goal entails the following work which we have completed
* Writing a C abstraction for an array of NeoPixel LEDs (Wesley)
* Writing functions that allow us to change the C abstraction of a NeoPixel LED (Wesley)
* Writing code that converts our abstraction into bits to be sent digitally (Alex)

It also entails the following task, which has proved difficult
* Sending the digital bits to control the LEDs at the appropriate speed (originally Alex, now both of us)

I believe we are close to 90% done; though the last 10% of the work is integrating all of the processing with the hardware. Specifically, we are struggling to set up the timer to run fast enough to hit the timing requirements of the Neopixel hardware.

### Key takeaway

Hardware Abstraction Layers (HALs) make it easy to start developing code on unfamiliar hardware. HAL's also make it hard to write very fast code. Trying to write fast code on unfamiliar hardware (i.e. writing low level code on that hardware) is very hard.

## Lessons Learned

* PLL's allow you to increase the speed of a clock signal ([link here](http://fastbitlab.com/stm32-pll-programming-fundamentals-2/))
* HAL's give you high level control over hardware, without having to really think about the hardware ([docs here](https://www.st.com/resource/en/user_manual/dm00154093-description-of-stm32f1-hal-and-lowlayer-drivers-stmicroelectronics.pdf))
* HAL's introduce overhead that slows down your code. This isn't an issue for most programs, but makes writing code that loops quickly nearly impossible.
    * The "official" implementation of the Neopixel library from Adafruit does not use a HAL; it actually is written in bare assembly code, presumably to meet the fast timing requirements


## Moving forward

* We are looking into using the PWM options in the HAL instead of manually flipping pins high and low to send data.
    * [This article](https://www.thevfdcollective.com/blog/stm32-and-sk6812-rgbw-led) describes a similar path to what we are considering; though we would need to update it for our hardware.
* We are also documenting our learning process. See `SETUP.md` for the beginnings of this documentation.

## Links

* [Trello](https://trello.com/b/4Y54vG8e/advancedblinky)
* [Github](https://github.com/awenstrup/AdvancedBlinky)
