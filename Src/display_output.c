#include <stdio.h>
#include "display_output.h"
#include "lcd.h"
#include "stm32f4xx_hal.h"

#define BUFF_SIZE 16

#define X_LEFT_MARGIN  1
#define Y_WINKEL_LABEL 1
#define Y_WINKEL_VALUE 2
#define Y_GESCHW_LABEL 4
#define Y_GESCHW_VALUE 5
#define Y_ERROR_MSG    7

char altWinkel[BUFF_SIZE] = "";
char altGeschw[BUFF_SIZE] = "";

void printLabels()
{
	lcdGotoXY(X_LEFT_MARGIN, Y_WINKEL_LABEL);
	lcdPrintS("Drehwinkel (Grad)");
	
	lcdGotoXY(X_LEFT_MARGIN, Y_GESCHW_LABEL);
	lcdPrintS("Drehgesch. (Grad/s)");
}

void printWinkel(double neuWinkel, int printCount)
{
	char neuTemp[BUFF_SIZE];
	sprintf(neuTemp, "%10.1f", neuWinkel);
	
	if (neuTemp[printCount] != altWinkel[printCount])
	{
		lcdGotoXY(X_LEFT_MARGIN + printCount, Y_WINKEL_VALUE);
		lcdPrintC(neuTemp[printCount]);
	}
	altWinkel[printCount] = neuTemp[printCount];
}

void printGeschw(double neuGeschw, int printCount)
{
	char neuTemp[BUFF_SIZE];
	sprintf(neuTemp, "%10.3f", neuGeschw);
	
	if (neuTemp[printCount] != altGeschw[printCount])
	{
		lcdGotoXY(X_LEFT_MARGIN + printCount, Y_GESCHW_VALUE);
		lcdPrintC(neuTemp[printCount]);
	}
	altGeschw[printCount] = neuTemp[printCount];
}

void printError()
{
	lcdGotoXY(X_LEFT_MARGIN, Y_ERROR_MSG);
	lcdPrintS("INVALID STATE: PRESS S6 TO RESET");
}

void clearError()
{
	lcdGotoXY(X_LEFT_MARGIN, Y_ERROR_MSG);
	lcdPrintS(" ");
}
