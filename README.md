# stm32f746ng_discovery_init
STM32F746NG - Discovery Board Setup

Frustrated with my experience initalizing the STM32F746NG discovery board, I wanted to
release this bare metal starting point.

This is my attempt at a no nonsense cpp starting point for experimenting with the discovery board.
It has all HAL modules in "stm32f7xx_hal_conf.h" enable by default. It initalizes the led on the
board to blink as well as setting up uarts on pins (RX-PC6/D1 TX-PC7/D0) and through the STLink.
I took all the initalization out of the "msp" file and organized it in main so it is easy to find.

The repo is setup to use "Visual GDB". It comes with a 30 free trial and is a fraction of the cost
of something like ARM MDK uVision.

For adding more periphrials I would recommend making a project in STM32Cube and copying the relevant
parts into this project.

GL friends!



