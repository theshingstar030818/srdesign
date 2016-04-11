/**
 *  InsulinQueue.h
 *
 *  Created on: Dec 5, 2015
 *      Author: sle
 */
 
#ifndef INSULINQUEUE_INSULINQUEUE_H_
#define INSULINQUEUE_INSULINQUEUE_H_

#include <stdbool.h>

#define INSULIN_QUEUE_SIZE 20
#define INSULIN_ACCEPTABLE_STEPS 1875

/** Function: InsulinQueue_Initiate()
 * 
 *  Sets up InsulinQueue.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void InsulinQueue_Initiate(void);

/** Function: InsulinQueue_Push()
 * 
 *  Pushes the currentInsulinAmount to the HEAD of InsulinQueue.
 *  
 *  @param uint32_t: currentInsulinAmount - current track of insulin
 *  @return void: void
 */
 
void InsulinQueue_Push(uint32_t currentInsulinAmount);

/** Function: InsulinQueue_ValidDose()
 * 
 *  Check to see if the last half of queue exceedes certain limit
 *  
 *  @param uint32_t: new_dose - the new dose being requested
 *  @return bool: whether or not more insulin can be injected
 */
 
bool InsulinQueue_ValidDose(uint32_t new_dose);

/** Function: TIMER2_IRQHandler()
 * 
 *  When Timer2 is trigged, push to the queue.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void TIMER2_IRQHandler(void);

#endif /* INSULINQUEUE_INSULINQUEUE_H_ */
