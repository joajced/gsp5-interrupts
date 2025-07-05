#include "led_io.h"
#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

int readEncoderInput()
{
	return GPIOF->IDR & 0x03;
}

void setLedD()
{
	GPIOD->ODR = currCount & 0xFF;
}

void setLedE()
{
	switch(currDir)
	{
		case FORWARD:   GPIOE->ODR = (1 << 7); break;
		case BACKWARD:  GPIOE->ODR = (1 << 6); break;
		case INVALID:   GPIOE->ODR = (1 << 5); break;
		case UNCHANGED: break;
	}
}

bool isS6Pressed()
{
	return !(GPIOF->IDR & (1 << 6));
}
