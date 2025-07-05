#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "LCD_GUI.h"
#include "init.h"
#include "lcd.h"
#include "encoder.h"
#include "timestamp.h"
#include "led_io.h"
#include "display_output.h"

#define ZEITFENSTER 250.0

int main()
{
	initITSboard();
	GUI_init(DEFAULT_BRIGHTNESS);
	lcdSetFont(20);
	printLabels();
	
	initTimer();
	uint32_t lastTimestamp = getTimestamp();
	int lastCount = 0;
	double winkel1, geschw1;
	
	int printCount = 0;
	currPhase = readEncoderInput();
	initInterrupts();
	
	while (1)
	{
		currTimestamp = getTimestamp();
		
		/************************************************
		 * 1. ERROR-ABFRAGE                             *
		 ************************************************/
		
		if (currDir == INVALID)
		{
			printError();
			setLedE();
			
			// Wartet bis S6 gedrückt wird -> Reset Error
			while (!isS6Pressed());
			clearError();
			currCount = 0;
			currPhase = readEncoderInput();
		}
		
		/************************************************
		 * 2. VERARBEITUNG                              *
		 ************************************************/
		
		double period = getPeriodMs(lastTimestamp, currTimestamp);
		
		if (period > (ZEITFENSTER + 50.0) || (period > ZEITFENSTER && currDir != UNCHANGED))
		{
			printCount = 0;
			
			winkel1 = calcWinkel();
			geschw1 = calcGeschw(lastCount, currCount, period);
			
			lastTimestamp = currTimestamp;
			lastCount = currCount;
		}
		
		/************************************************
		 * 3. LED- UND BILDSCHIRMAUSGABE                *
		 ************************************************/
		
		if (currDir != UNCHANGED)
		{
			setLedD();
			setLedE();
		}
		
		if (printCount < 20)
		{
			printCount < 10 ? printWinkel(winkel1, printCount) : printGeschw(geschw1, printCount - 10);
			printCount++;
		}
	}
}
