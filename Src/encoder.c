#include "encoder.h"
#include "timestamp.h"
#include "stm32f4xx_hal.h"

#define WINKEL_PRO_SCHRITT 0.3 // = 360° / 1200

Direction transitions[4][4] =
{        /*   A   |   D   |   B   |   C   */
	/* A */ {UNCHANGED, BACKWARD, FORWARD, INVALID},
	/* D */ {FORWARD, UNCHANGED, INVALID, BACKWARD},
	/* B */ {BACKWARD, INVALID, UNCHANGED, FORWARD},
	/* C */ {INVALID, FORWARD, BACKWARD, UNCHANGED}
};

// Zustandsvariablen
volatile Phase currPhase = PHASE_A;
volatile Direction currDirection = UNCHANGED;
volatile int count = 0;
volatile uint32_t lastTimestamp;
volatile bool fehlerzustand = false;

void EXTI0_IRQHandler(void)
{	
	uint8_t PG0    = GPIOG->IDR & 0x01;
	Phase newPhase = (currPhase & 0x02) | PG0;
	
	currDirection = transitions[currPhase][newPhase];
	switch(currDirection)
	{
		case FORWARD:   count++; break;
		case BACKWARD:  count--; break;
		case INVALID:   resetState(); fehlerzustand = true; break;
		case UNCHANGED: break;
	}
	
	currPhase = newPhase;
	EXTI->PR = (1 << 0); // Reset INT0
}

void EXTI1_IRQHandler(void)
{
	uint8_t PG1    = (GPIOG->IDR >> 1) & 0x01;
	Phase newPhase = PG1 | (currPhase & 0x01);
	
	currDirection = transitions[currPhase][newPhase];
	switch(currDirection)
	{
		case FORWARD:   count++; break;
		case BACKWARD:  count--; break;
		case INVALID:   resetState(); break;
		case UNCHANGED: break;
	}
	
	currPhase = newPhase;
	EXTI->PR = (1 << 1); // Reset INT1
}

int getCount()
{
	return count;
}

void resetState()
{
	currPhase = PHASE_A;
	currDirection = UNCHANGED;
	count = 0;
}

bool isFehlerzustand()
{
	return fehlerzustand;
}

void resetFehlerzustand()
{
	fehlerzustand = false;
}

double calcWinkel()
{
	return count * WINKEL_PRO_SCHRITT;
}

double calcGeschw(int count1, int count2, double periode)
{
	double steps = (double) count2 - count1;
	return (steps / (periode / 1000)) * WINKEL_PRO_SCHRITT;
}
