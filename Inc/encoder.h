#ifndef ENCODER_H
#define ENCODER_H

typedef enum
{
	PHASE_A = 0x00,
	PHASE_B = 0x10,
	PHASE_C = 0x11,
	PHASE_D = 0x01
} Phase;

typedef enum
{
	FORWARDS,
	BACKWARDS,
	INVALID,
	NO_CHANGE
} Direction;

int setPhase(int newPhase, int currPhase, Direction* dir);

int getCount();

void resetCount();

double calcWinkel();

double calcGeschw(int count1, int count2, double periode);

#endif
