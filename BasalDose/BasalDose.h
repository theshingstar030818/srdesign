/**
 *  BasalDose.h
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#ifndef BASALDOSE_H_
#define BASALDOSE_H_


/** Function: BasalDose_DoseTimingInitiate()
 * 
 *  Sets up and enables Timer0.
 *  
 *  @param void: void
 *  @return void: void
 */

void BasalDose_DoseTimingInitiate(void);

/** Function: BasalDose_DoseTimingEnable()
 *  
 *  Function is used to enable Timer0 counter,
 *  then disables and resets Timer1.
 *  
 *  @param void: void
 *  @return void: void
 */

void BasalDose_DoseTimingEnable(void);

/** Function: BasalDose_DoseTimingDisable()
 *  
 *  Function is used to disable and reset Timer0.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void BasalDose_DoseTimingDisable(void);

/** Function: BasalDose_DoseTimingReset()
 *  
 *  Resets all pending Timer0 interrupts and clears out counters.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void BasalDose_DoseTimingReset(void);

/** Function: BasalDose_DoseInitiate()
 * 
 *  Sets up and enables Timer1.
 *
 *	@param void: void
 *	@return void: void
 */

void BasalDose_DoseInitiate(void);

/** Function: BasalDose_DoseEnable()
 * 
 *  Function is used to enable Timer1 counter,
 *  then disables and resets Timer0.
 *	
 *	@param void: void
 *	@return void: void
 */

void BasalDose_DoseEnable(void);

/** Function: BasalDose_DoseDisable()
 *  
 *  Function is used to disable and reset Timer1.
 *  
 *  @param void: void
 *  @return void: void
 */

void BasalDose_DoseDisable(void);

/** Function: BasalDose_DoseReset()
 *  
 *  Function is used to disable and reset Timer1.
 *  
 *  @param void: void
 *  @return void: void
 */

void BasalDose_DoseReset(void);

/** Function: TIMER0_IRQHandler()
 *  
 *  Sets the GlobalStatus depending on how much is left in the syringe.
 *  
 *  @param void: void
 *  @return void: void
 */
void TIMER0_IRQHandler(void);

/** Function: TIMER1_IRQHandler()
 *  
 *  Depending on the GlobalStatus, administer dosages accordingly.
 *  
 *  @param void: void
 *  @return void: void
 */

void TIMER1_IRQHandler(void);

#endif /* BASALDOSE_H_ */
