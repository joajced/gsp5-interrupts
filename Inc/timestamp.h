#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <stm32f4xx_hal.h>
#include "timer.h"

uint32_t getTimestamp();

double getPeriodMs(uint32_t t1, uint32_t t2);

#endif
