#ifndef ENCODER_H
#define ENCODER_H

extern int count;

typedef enum
{
	PHASE_A = 0x00,
	PHASE_B = 0x10,
	PHASE_C = 0x11,
	PHASE_D = 0x01
} Phase;

typedef enum
{
	FORWARD,
	BACKWARD,
	INVALID,
	UNCHANGED
} Direction;

void updateDirection(Phase newPhase, Phase currPhase, Direction* currDir);

double calcWinkel();

double calcGeschw(int count1, int count2, double periode);

#endif
