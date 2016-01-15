 /**
 *  InsulinQueue.c
 *
 *  Created on: Dec 5, 2015
 *      Author: sle
 */
 
#include "./InsulinQueue.h"

InsulinQueue *InsulinQueue_Create(uint32_t maxEntries)
{
	InsulinQueue *iq;
	iq = (InsulinQueue *)malloc(sizeof(InsulinQueue));
	
	iq->maxNumEntries = maxEntries;
	iq->currentNumEntries = 0;
	iq->head = 0;
	iq->tail = -1;
	iq->insulinEntry = (uint32_t *)malloc(sizeof(uint32_t) * maxEntries);
	
	return iq;
}

void InsulinQueue_Pop(InsulinQueue *iq)
{
	if(iq->currentNumEntries == 0)
	{
		return;
	}
	else
	{
		iq->currentNumEntries--;
		iq->head++;
		
		if(iq->head == iq->maxNumEntries)
			iq->head = 0;
		
	}
	return;
}

void InsulinQueue_Push(InsulinQueue *iq, int currentInsulinAmount)
{
	if(iq->currentNumEntries == iq->maxNumEntries)
	{
		InsulinQueue_Pop(iq);
		InsulinQueue_Push(iq, currentInsulinAmount);
	}
	else
	{
		iq->currentNumEntries++;
		iq->tail++;
		iq->insulinEntry[iq->tail] = currentInsulinAmount;
	}
}
