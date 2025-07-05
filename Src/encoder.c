#include "encoder.h"
#include "led_io.h"

#define WINKEL_PRO_SCHRITT 0.3 // =360/1200

int count = 0;

Direction transitions[4][4] =
{        /*   A   |   D   |   B   |   C   */
	/* A */ {UNCHANGED, BACKWARD, FORWARD, INVALID},
	/* D */ {FORWARD, UNCHANGED, INVALID, BACKWARD},
	/* B */ {BACKWARD, INVALID, UNCHANGED, FORWARD},
	/* C */ {INVALID, FORWARD, BACKWARD, UNCHANGED}
};

void updateDirection(Phase newPhase, Phase currPhase, Direction* currDir)
{
	Direction newDir = transitions[currPhase][newPhase];
	switch (newDir)
	{
		case FORWARD:
			count++;
			break;
		case BACKWARD:
			count--;
			break;
		case INVALID:   break;
		case UNCHANGED: break;
	}
	
	*currDir = newDir;
}

double calcWinkel()
{
	return count * WINKEL_PRO_SCHRITT;
}

double calcGeschw(int count1, int count2, double periode)
{
	double steps = (double) count2 - count1;
	return (steps / (periode/ 1000)) * WINKEL_PRO_SCHRITT;
}
