#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "lcd.h"

#include "encoder.h"
#include "gpio.h"
#include "display_output.h"
#include "timestamp.h"

#define ZEITFENSTER 250.0 /*ms*/

int main()
{
	initITSboard();
	GUI_init(DEFAULT_BRIGHTNESS);
	lcdSetFont(20);
	
	initInterrupts();
	printLabels();
	initTimer();
	
	uint32_t t1 = getTimeStamp();
	
	while (1)
	{
		double period = getPeriodMs(t1, getTimeStamp());
		
		if (isFehlerzustand())
		{
			printError();
			
			while (!readButtonF(6));
			clearError();
			resetState();
		}
		
		if (period > ZEITFENSTER)
		{
			char temp[16];
			double winkel = calcWinkel();
			sprintf(temp, "%10.1f", winkel);
			lcdGotoXY(1, 2);
			lcdPrintReplS(temp);
			
			t1 = getTimeStamp();
		}
	}
}
