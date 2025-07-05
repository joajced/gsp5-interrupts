#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <stm32f4xx_hal.h>
#include "timer.h"

#define GET_TIMESTAMP() (TIM2->CNT)

double getPeriodMs(uint32_t t1, uint32_t t2);

#endif
