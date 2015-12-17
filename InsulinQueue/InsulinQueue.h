/**
 *  InsulinQueue.h
 *
 *  Created on: Dec 5, 2015
 *      Author: sle
 */
#include <stdlib.h>
#include "..\Control.h"

typedef struct InsulinQueue
{
	uint32_t maxNumEntries;
	uint32_t currentNumEntries;
	int head;
	int tail;
	uint32_t *insulinEntry;
} InsulinQueue;


InsulinQueue *createInsulinQueue(uint32_t maxEntries);

void pop(InsulinQueue *iq);

void push(InsulinQueue *iq, int currentInsulinAmount);
