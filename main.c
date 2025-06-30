#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "lcd.h"

#include "encoder.h"
#include "led_io.h"
#include "display_output.h"
#include "timestamp.h"

// Zeitfenster für Geschwindigkeitsberechnung in ms
#define ZEITFENSTER 250.0

Phase currPhase; // Letzte Phase des Encoders
Phase newPhase;

int main()
{
	initITSboard();
	GUI_init(DEFAULT_BRIGHTNESS);
	lcdSetFont(20);
	
	// Initialisierung
	printLabels();
	initTimer();
	uint32_t time1 = getTimestamp();
	int count1 = getCount();
	double winkel1;
	double geschw1;
	currPhase = readLedF();
	newPhase = readLedF();
	int printCount = 0;
	Direction dir = NO_CHANGE;
	
	while (1)
	{
		// 1. Eingabe
		newPhase = readLedF();  // Aktuelle Phase von den GPIOs lesen
		uint32_t time2 = getTimestamp(); // Zeitdifferenz berechnen
		
		// Error Abfrage
		if (setPhase(newPhase, currPhase, &dir))
		{
			printError();
			
			while (!readButtonF(6));
			clearError();
			resetCount();
			currPhase = newPhase = readLedF();
		}
		
		// 2. Verarbeitung
		int count2 = getCount();
		double period = getPeriodMs(time1, time2);
		
		// Nur berechnen und drucken wenn genug Zeit vergangen ist (ZEITFENSTER)
		if (period > (ZEITFENSTER + 50.0) || (period > ZEITFENSTER && newPhase != currPhase))
		{
			printCount = 0;
			
			winkel1 = calcWinkel();
			geschw1 = calcGeschw(count1, count2, period);
			
			time1 = time2;	
			count1 = count2;
		}
		
		// 3. Bildschirm-Ausgabe
		if (printCount < 20)
		{
			printCount < 10 ? printWinkel(winkel1, printCount)
											: printGeschw(geschw1, printCount - 10);
			printCount++;
		}
		
		currPhase = newPhase;
	}
}
