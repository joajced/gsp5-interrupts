#include "encoder.h"
#include "led_io.h"
#include "timestamp.h"
#include "stm32f4xx_hal.h"

int count = 0; // Zählvariable für Encoder-Position

#define WINKEL_PRO_SCHRITT 0.3 // 360° / 1200

Direction transitions[4][4] =
{ /*           A    |    D    |    B    |    C    */
	/* A */ {NO_CHANGE, BACKWARDS, FORWARDS, INVALID},
	/* D */ {FORWARDS, NO_CHANGE, INVALID, BACKWARDS},
	/* B */ {BACKWARDS, INVALID, NO_CHANGE, FORWARDS},
	/* C */ {INVALID, FORWARDS, BACKWARDS, NO_CHANGE}
};

int setPhase(int newPhase, int currPhase, Direction *dir)
{
	Direction currDir = transitions[currPhase][newPhase];
	
	switch(currDir)
	{
		case FORWARDS:
			count++;
			break;
		case BACKWARDS:
			count--;
			break;
		case INVALID:
			count = 0;
			*dir = currDir;
			return -1;
		case NO_CHANGE:
			break;
	}
	*dir = currDir;
	return 0;
}

int getCount()
{
	return count;
}

void resetCount()
{
	count = 0;
}

double calcWinkel()
{
	return getCount() * WINKEL_PRO_SCHRITT;
}

double calcGeschw(int count1, int count2, double periode)
{
	double steps = (double) count2 - count1;
	return (steps / (periode / 1000)) * WINKEL_PRO_SCHRITT;
}
