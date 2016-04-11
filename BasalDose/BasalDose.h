/**
 *  BasalDose.h
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#ifndef BASALDOSE_H_
#define BASALDOSE_H_

/** Function: BasalDose_TimingInitiate()
 * 
 *  Sets up and enables Timer0.
 *  
 *  @param void: void
 *  @return void: void
 */

void BasalDose_TimingInitiate(void);

/** Function: BasalDose_TimingEnable()
 *  
 *  Function is used to enable Timer0 counter,
 *  then disables and resets Timer1.
 *  
 *  @param void: void
 *  @return void: void
 */

void BasalDose_TimingEnable(void);

/** Function: BasalDose_TimingDisable()
 *  
 *  Function is used to disable and reset Timer0.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void BasalDose_TimingDisable(void);

/** Function: TIMER0_IRQHandler()
 *  
 *  Sets the GlobalStatus depending on how much is left in the syringe.
 *  Ensures no overdose.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void TIMER0_IRQHandler(void);

#endif /* BASALDOSE_H_ */
