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
	
	Phase currPhase = readEncoderInput();
	Phase newPhase  = readEncoderInput();
	Direction currDir = UNCHANGED;
	
	int count1 = count;
	double winkel1, geschw1;
	
	int printCount = 0;
	
	initTimer();
	uint32_t t1 = getTimestamp();
	
	while (1)
	{
		/* Oszilloskop D16
		 * int a = getTimestamp();
		 * GPIOE->BSRR = 1;
		 */
		
		/************************************************
		 * 1. EINGABE                                   *
		 ************************************************/
		
		newPhase = readEncoderInput();
		uint32_t t2 = getTimestamp();
		
		/************************************************
		 * 2. ERROR-ABFRAGE                             *
		 ************************************************/
		
		updateDirection(newPhase, currPhase, &currDir);
		if (currDir == INVALID)
		{
			printError();
			setLedE(INVALID);
			
			// Wartet bis S6 gedrückt wird -> Reset Error
			while (!isS6Pressed());
			clearError();
			count = 0;
			currPhase = newPhase = readEncoderInput();
		}
		
		/************************************************
		 * 3. VERARBEITUNG                              *
		 ************************************************/
		
		int count2 = count;
		double period = getPeriodMs(t1, t2);
		
		// Nur berechnen und drucken wenn genug ZEITFENSTER vergangen ist
		if (period > (ZEITFENSTER + 50.0) || (period > ZEITFENSTER && newPhase != currPhase))
		{
			printCount = 0;
			
			winkel1 = calcWinkel();
			geschw1 = calcGeschw(count1, count2, period);
			
			t1 = t2;	
			count1 = count2;
		}
		
		/************************************************
		 * 4. AUSGABE                                   *
		 ************************************************/
		
		if (newPhase != currPhase)
		{
			setLedD(count2);
			setLedE(currDir);
		}
		
		if (printCount < 20)
		{
			printCount < 10 ? printWinkel(winkel1, printCount) : printGeschw(geschw1, printCount - 10);
			printCount++;
		}
		
		currPhase = newPhase;
		
		/* Oszilloskop D16
		 * GPIOE->BSRR = (1 << 16);
		 * int b = getTimestamp();
		 * printf("%f \n", getPeriodMs(a,b));
		 */
	}
}
