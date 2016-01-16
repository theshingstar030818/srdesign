 /**
 *  InsulinQueue.c
 *
 *  Created on: Dec 5, 2015
 *      Author: sle
 */
 
#include "./InsulinQueue.h"

extern uint32_t StepperMotor_GlobalPosition;

InsulinQueue *globalIQ;

void InsulinQueue_Initiate()
{
	LPC_TIM2->PR = 0x02; // Pre-scalar
	LPC_TIM2->MR0 = 1 << 28; // Match number
	LPC_TIM2->MCR |= 3 << 0; // Interrupt and reset timer on match (MCR = 011)
	NVIC_EnableIRQ(TIMER2_IRQn);
	LPC_TIM2->TCR |= 1 << 0;
}

InsulinQueue *InsulinQueue_Create(uint32_t maxEntries)
{
	InsulinQueue *iq;
	int i;
	iq = (InsulinQueue *)malloc(sizeof(InsulinQueue));
	
	iq->maxNumEntries = maxEntries;
	iq->curNumEntries = 0;
	iq->head = 0;
	iq->tail = -1;
	iq->insulinEntry = (uint32_t *)malloc(sizeof(uint32_t) * maxEntries);
	
	for(i = 0; i < maxEntries; i++)
	{
		iq->insulinEntry[i] = 0;
	}
	
	return iq;
}

void InsulinQueue_Push(InsulinQueue *iq, int currentInsulinAmount)
{
	if(iq->curNumEntries == iq->maxNumEntries)
	{
		InsulinQueue_Pop(iq);
		InsulinQueue_Push(iq, currentInsulinAmount);
	}
	else
	{
		iq->curNumEntries++;
		iq->tail++;
		
		if(iq->tail == iq->maxNumEntries)
			iq->tail =0;
		
		iq->insulinEntry[iq->tail] = currentInsulinAmount;
	}
	return;
}

void InsulinQueue_Pop(InsulinQueue *iq)
{
	if(iq->curNumEntries != 0)
	{
		iq->curNumEntries--;
		iq->head++;
		
		if(iq->head == iq->maxNumEntries)
			iq->head = 0;	
	}
	return;
}

void TIMER2_IRQHandler(void)
{
	InsulinQueue_Push(globalIQ, StepperMotor_GlobalPosition);
	LPC_TIM2->IR |= 1 << 0; // Clear out Timer2 registers
}
