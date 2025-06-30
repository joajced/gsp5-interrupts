#include "timestamp.h"

uint32_t getTimestamp()
{
	return TIM2->CNT;
}

double getPeriodMs(uint32_t t1, uint32_t t2)
{
	double diff = t2 - t1;
	return diff / 90000.0;
}
