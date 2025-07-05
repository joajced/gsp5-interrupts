#ifndef LED_IO_H
#define LED_IO_H

#include <stdbool.h>
#include "encoder.h"

int readEncoderInput();

void setLedD();

void setLedE();

bool isS6Pressed();

#endif
