#ifndef LED_IO_H
#define LED_IO_H

#include <stdbool.h>
#include "encoder.h"

#define READ_ENCODER_INPUT() (GPIOG->IDR & 0x03)
#define SET_LED_D() (GPIOD->ODR = currCount & 0xFF)

bool isS6Pressed();

#endif
