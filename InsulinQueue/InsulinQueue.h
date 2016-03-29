/**
 *  InsulinQueue.h
 *
 *  Created on: Dec 5, 2015
 *      Author: sle
 */
 
#ifndef INSULINQUEUE_INSULINQUEUE_H_
#define INSULINQUEUE_INSULINQUEUE_H_

#define INSULIN_QUEUE_SIZE 20

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

/** Function: TIMER2_IRQHandler()
 * 
 *  When Timer2 is trigged, push to the queue.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void TIMER2_IRQHandler(void);

#endif /* INSULINQUEUE_INSULINQUEUE_H_ */
