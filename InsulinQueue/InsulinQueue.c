 /**
 *  InsulinQueue.c
 *
 *  Created on: Dec 5, 2015
 *      Author: sle
 */
 
#include "./InsulinQueue.h"

extern uint32_t StepperMotor_GlobalPosition;

uint32_t InsulinQueue_Queue[INSULIN_QUEUE_SIZE];
uint32_t *pInsulinQueue_Queue;
uint32_t InsulinQueue_Head;

void InsulinQueue_Initiate()
{
	LPC_TIM2->PR = 0x02; // Pre-scalar
	LPC_TIM2->MR0 = 1 << 27; // Match number
	LPC_TIM2->MCR |= 3 << 0; // Interrupt and reset timer on match (MCR = 011)
	NVIC_EnableIRQ(TIMER2_IRQn);
	LPC_TIM2->TCR |= 1 << 0;
	InsulinQueue_Head = 0;
}

void InsulinQueue_Push(uint32_t currentInsulinAmount)
{
	// If queue is maxed, reset head first, then just insert element
	if(InsulinQueue_Head == INSULIN_QUEUE_SIZE)
	{
		InsulinQueue_Head = 0;
	}
	
	*(pInsulinQueue_Queue + InsulinQueue_Head) = currentInsulinAmount;
	InsulinQueue_Head++;
}

void TIMER2_IRQHandler(void)
{
	InsulinQueue_Push(StepperMotor_GlobalPosition);
	LPC_TIM2->IR |= 1 << 0; // Clear out Timer2 registers
}
