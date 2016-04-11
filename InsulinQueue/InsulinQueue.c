 /**
 *  InsulinQueue.c
 *
 *  Created on: Dec 5, 2015
 *      Author: sle
 */
 
#include "..\Control.h"
#include ".\InsulinQueue.h"
#include "..\StepperMotor\StepperMotor.h"

extern uint32_t StepperMotor_GlobalPosition;

uint32_t InsulinQueue_Head;
uint32_t *pInsulinQueue_Queue;
uint32_t InsulinQueue_CurrentEntryCount;
uint32_t InsulinQueue_Queue[INSULIN_QUEUE_SIZE];

void InsulinQueue_Initiate()
{
	uint32_t i;
	
	LPC_TIM2->PR = 0; // Pre-scalar
	LPC_TIM2->MR0 = 750000000;; // Match number
	LPC_TIM2->MCR |= 3 << 0; // Interrupt and reset timer on match (MCR = 011)
	NVIC_EnableIRQ(TIMER2_IRQn);
	LPC_TIM2->TCR |= 1 << 0;
	InsulinQueue_Head = 0;
	
	InsulinQueue_CurrentEntryCount = 0;
	for(i = 0; i < INSULIN_QUEUE_SIZE; i++)
	{
		InsulinQueue_Queue[i] = 0;
	}
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

bool InsulinQueue_ValidDose(uint32_t new_dose)
{
	uint32_t i, current_dose = 0;
	
	// Since we are on a ten minute queue, track last five minutes and current minute.
	if(InsulinQueue_Head >= INSULIN_QUEUE_SIZE / 2)
	{
		for(i = InsulinQueue_Head - INSULIN_QUEUE_SIZE / 2; i < InsulinQueue_Head; i++)
		{
			current_dose += InsulinQueue_Queue[i];
		}
		current_dose += InsulinQueue_CurrentEntryCount;
	}
	else
	{
		for(i = 0; i < InsulinQueue_Head; i++)
		{
			current_dose += InsulinQueue_Queue[i];
		}
		for(i = INSULIN_QUEUE_SIZE - 1; i >= INSULIN_QUEUE_SIZE - ((INSULIN_QUEUE_SIZE / 2) - InsulinQueue_Head); i--)
		{
			current_dose += InsulinQueue_Queue[i];
		}
		current_dose += InsulinQueue_CurrentEntryCount;
	}
	return current_dose + new_dose < INSULIN_ACCEPTABLE_STEPS;
}

void TIMER2_IRQHandler(void)
{
	InsulinQueue_Push(InsulinQueue_CurrentEntryCount);
	InsulinQueue_CurrentEntryCount = 0;
	LPC_TIM2->IR |= 1 << 0; // Clear out Timer2 registers
}
