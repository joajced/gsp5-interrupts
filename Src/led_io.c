#include "led_io.h"
#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

int readLedF()
{
	return GPIOF->IDR & 0x03;
}

bool readButtonF(int offset)
{
	int maskSet = (0x01 << offset);
	int input = GPIOF->IDR;
	
	return maskSet != (input & maskSet);
}
