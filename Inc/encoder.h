#ifndef ENCODER_H
#define ENCODER_H

#include <stm32f4xx_hal.h>

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

// Deklaration globaler Variablen
volatile extern Phase     currPhase, newPhase;
volatile extern int       currCount;
volatile extern Direction currDir;
volatile extern uint32_t  currTimestamp;

void initInterrupts();

double calcWinkel();

double calcGeschw(int count1, int count2, double periode);

#endif
