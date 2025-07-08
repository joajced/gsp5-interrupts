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
	uint32_t lastTimestamp = GET_TIMESTAMP();
	int lastCount = 0;
	double winkel1, geschw1;
	
	int printCount = 0;
	currPhase = READ_ENCODER_INPUT();
	initInterrupts();
	
	while (1)
	{
		currTimestamp = GET_TIMESTAMP();
		
		/************************************************
		 * 1. ERROR-ABFRAGE                             *
		 ************************************************/
		
		if (currDir == INVALID)
		{
			printError();
			while (!isS6Pressed());
			clearError();
			currCount = 0;
			currPhase = READ_ENCODER_INPUT();
		}
		
		/************************************************
		 * 2. VERARBEITUNG                              *
		 ************************************************/
		
		double period = getPeriodMs(lastTimestamp, currTimestamp);
		
		if (period > (ZEITFENSTER + 50.0) || (period > ZEITFENSTER && currDir != UNCHANGED))
		{
			printCount = 0;
			
			// Neueste Daten für die Berechnung abfragen
			// Deren Werte werden auf dem Display ausgegeben, jedoch nirgendwohin gespeichert
			uint32_t currTimestampPRINT = GET_TIMESTAMP();
			int currCountPRINT = currCount;
			
			double periodPRINT = getPeriodMs(lastTimestamp, currTimestampPRINT);
			
			winkel1 = currCountPRINT * 0.3;
			geschw1 = calcGeschw(lastCount, currCountPRINT, periodPRINT);
			
			lastTimestamp = currTimestamp;
			lastCount = currCount;
		}
		
		/************************************************
		 * 3. LED- UND BILDSCHIRMAUSGABE                *
		 ************************************************/
		
		SET_LED_D();
		if (printCount < 20)
		{
			printCount < 10 ? printWinkel(winkel1, printCount) : printGeschw(geschw1, printCount - 10);
			printCount++;
		}
	}
}
