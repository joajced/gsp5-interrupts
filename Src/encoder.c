#include <stm32f4xx_hal.h>
#include "encoder.h"
#include "led_io.h"
#include "timestamp.h"

#define WINKEL_PRO_SCHRITT 0.3 // =360/1200

// Initialisierung globaler Variablen
volatile Phase currPhase = PHASE_A;
volatile Phase newPhase  = PHASE_A;
volatile int       currCount = 0;
volatile Direction currDir   = UNCHANGED;
volatile uint32_t  currTimestamp = 0;

Direction transitions[4][4] =
{        /*   A   |   D   |   B   |   C   */
	/* A */ {UNCHANGED, BACKWARD, FORWARD, INVALID},
	/* D */ {FORWARD, UNCHANGED, INVALID, BACKWARD},
	/* B */ {BACKWARD, INVALID, UNCHANGED, FORWARD},
	/* C */ {INVALID, FORWARD, BACKWARD, UNCHANGED}
};

void initInterrupts()
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;     // Clock for GPIO Port G
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;    // System conf. Clock enable
	// Routing Pin 0 of Port G -> EXTI0
	SYSCFG->EXTICR[0] &= ~(0x0f << (4 * 0)); // Remove old selection
	SYSCFG->EXTICR[0] |=   0x06 << (4 * 0);  // 0x06 : Select port G
	// Routing Pin 1 of Port G -> EXTI1
	SYSCFG->EXTICR[0] &= ~(0x0f << (4 * 1)); // Remove old selection
	SYSCFG->EXTICR[0] |=   0x06 << (4 * 1);  // 0x06 : Select port G
	
	EXTI->RTSR |= (1 << 0); // Select rising trigger for INT0
	EXTI->FTSR |= (1 << 0); // Select falling trigger for INT0
	EXTI->IMR  |= (1 << 0); // Unmask INT0
	EXTI->RTSR |= (1 << 1); // Select rising trigger for INT1
	EXTI->FTSR |= (1 << 1); // Select falling trigger for INT1
	EXTI->IMR  |= (1 << 1); // Unmask INT1
	
	NVIC_SetPriorityGrouping(0); // Setup interrupt controller
	NVIC_SetPriorityGrouping(1); // Setup interrupt controller
	NVIC_SetPriority(EXTI0_IRQn, 8);
	NVIC_SetPriority(EXTI1_IRQn, 8);
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
}

void EXTI0_IRQHandler(void)
{
	currTimestamp = getTimestamp();
	newPhase = GPIOG->IDR & 0x03;
	currDir = transitions[currPhase][newPhase];
	switch(currDir)
	{
		case FORWARD:   currCount++; break;
		case BACKWARD:  currCount--; break;
		case INVALID:   break;
		case UNCHANGED: break;
	}
	currPhase = newPhase;
	EXTI->PR = (1 << 0); // Reset INT0
}

void EXTI1_IRQHandler(void)
{
	currTimestamp = getTimestamp();
	newPhase = GPIOG->IDR & 0x03;
	currDir = transitions[currPhase][newPhase];
	switch(currDir)
	{
		case FORWARD:   currCount++; break;
		case BACKWARD:  currCount--; break;
		case INVALID:   break;
		case UNCHANGED: break;
	}
	currPhase = newPhase;
	EXTI->PR = (1 << 1); // Reset INT1
}

double calcWinkel()
{
	return currCount * WINKEL_PRO_SCHRITT;
}

double calcGeschw(int count1, int count2, double periode)
{
	double steps = (double) count2 - count1;
	return (steps / (periode / 1000)) * WINKEL_PRO_SCHRITT;
}
