#include "timestamp.h"
#include "stm32f4xx_hal.h"

double getPeriodMs(uint32_t t1, uint32_t t2)
{
	double diff = t2 - t1;
	return diff / 90000.0;
}
