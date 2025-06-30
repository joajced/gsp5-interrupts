#include <stdio.h>
#include "display_output.h"
#include "lcd.h"
#include "stm32f4xx_hal.h"

#define ARRAY_SIZE 16

char altWinkel[ARRAY_SIZE] = "";
char altGeschw[ARRAY_SIZE] = "";

void printLabels()
{
	lcdGotoXY(1,1);
	lcdPrintS("Drehwinkel in Grad");
	
	lcdGotoXY(1,4);
	lcdPrintS("Drehgesch. in Grad/Sek.");
}

void printError()
{
	lcdGotoXY(1, 8);
	lcdPrintS("ERROR: INVALID STATE");
}

void clearError()
{
	lcdGotoXY(1, 8);
	lcdPrintS(" ");	// Löscht alles rechts vom Cursor
}

void printWinkel(double neuWinkel, int printCount)
{
	char neuTemp[ARRAY_SIZE];
	sprintf(neuTemp, "%10.1f", neuWinkel);
	
	if (neuTemp[printCount] != altWinkel[printCount])
	{
		lcdGotoXY((1 + printCount), 2);
		char print = neuTemp[printCount];
		lcdPrintC(print);
	}
	altWinkel[printCount] = neuTemp[printCount];
}

void printGeschw(double neuGeschw, int printCount)
{	
	char neuTemp[ARRAY_SIZE];
	sprintf(neuTemp, "%10.3f", neuGeschw);
	
	if (neuTemp[printCount] != altGeschw[printCount])
	{
		lcdGotoXY((1 + printCount), 5);
		char print = neuTemp[printCount];
		lcdPrintC(print);
	}
	altGeschw[printCount] = neuTemp[printCount];
}
