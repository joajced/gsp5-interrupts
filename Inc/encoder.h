#ifndef ENCODER_H
#define ENCODER_H

#include <stdbool.h>

typedef enum
{
	PHASE_A = 0x00u,
	PHASE_B = 0x10u,
	PHASE_C = 0x11u,
	PHASE_D = 0x01u
} Phase;

typedef enum
{
	FORWARD,
	BACKWARD,
	INVALID,
	UNCHANGED
} Direction;

int getCount();

void resetState();

bool isFehlerzustand();

void resetFehlerzustand();

double calcWinkel();

double calcGeschw(int count1, int count2, double periode);

#endif
