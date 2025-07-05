#include "led_io.h"
#include <stdio.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

bool isS6Pressed()
{
	return !(GPIOF->IDR & (1 << 6));
}
