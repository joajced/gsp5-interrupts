#ifndef LED_IO_H
#define LED_IO_H

#include <stdbool.h>
#include "encoder.h"

int readEncoderInput();

void setLedD(int count);

void setLedE(Direction dir);

bool isS6Pressed();

#endif
