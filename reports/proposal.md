# AdvancedBlinky: Running a NeoPixel array from an STM32 Microcontroller

### Team members
Alex Wenstrup
Wesley Soo-Hoo

### Project Goal
The purpose of this project is to develop a NeoPixel library that runs on STM32 microcontrollers. Currently, the NeoPixel only has official libraries for Arduinos, however, they have limited peripherals and processing power. The STM32 family, however, are 32 bit microcontrollers that have a wide range of peripherals, flash memory, and RAM that make them suited for a wide range of applications.

The lower bound for this project would be to develop a library that can control a single NeoPixel. The stretch goal would be to have a hardware-agnostic library that can control the entire range of NeoPixels that is supported by the hardware and easily be ported to other microcontrollers.

### Learning Goals
* Alex: My learning goals for this project are to get experience developing with STM32 Microcontrollers. I have worked with Arduinos and other AVR8 microcontrollers in the past, but have never worked with ARM chips. I would like to get exposure to this new technology. I would also like to get some reverse-engineering experience, which we should be able to get with this project.

* Wesley: My learning goals for this project are to increase my comfort with embedded development and to get more experience debugging on the firmware/hardware boundary. Additionally, I want to work more on developing an intuition for writing clean C code, especially keeping in mind reusability across multiple projects.

### Getting Started

To get started, we need to first acquire hardware. We’re considering using the [STM32 Blue Pill](https://www.amazon.com/Aideepen-Programming-Emulator-Downloader-STM32F103C8T6/dp/B07WRL3DF8/ref=sr_1_2?dchild=1&keywords=stm32+blue+pill&qid=1614184271&sr=8-2) development boards and a [NeoPixel Strip](https://www.amazon.com/gp/product/B00XQN3AF0?pf_rd_r=QPFCS1TBB2FRQAD8C17E&pf_rd_p=5ae2c7f8-e0c6-4f35-9071-dc3240e894a8&pd_rd_r=b1502783-4bae-4ad1-a084-554f00131ca3&pd_rd_w=V7P5y&pd_rd_wg=h9oRC&ref_=pd_gw_unk) to start with. There will be a bit of hardware bringup, but that will be relatively quick compared to the firmware challenges. We will also need to read through the NeoPixel documentation, which uses a proprietary communication protocol.

### First Steps

The first steps of this project will be to research the communication protocol used by the NeoPixels. There is a good amount of documentation linked on the [Adafruit Website](https://www.adafruit.com/category/168) and the [official library](https://github.com/adafruit/Adafruit_NeoPixel) is open source on Github. We will also need to order breakout boards and lights. Finally, we will need to find and understand a suitable buildchain for STM32 development. 
