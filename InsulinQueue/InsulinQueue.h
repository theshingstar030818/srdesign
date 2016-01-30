/**
 *  InsulinQueue.h
 *
 *  Created on: Dec 5, 2015
 *      Author: sle
 */
 
#include "..\Control.h"

#define INSULIN_QUEUE_SIZE 20

void InsulinQueue_Initiate(void);

void InsulinQueue_Push(uint32_t currentInsulinAmount);
