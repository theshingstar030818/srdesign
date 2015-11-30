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
 *  Must be called at the beginning of the main method.
 *  Currently, set up and enables Timer0.
 *  
 *  @param void: void
 *  @return void: void
 */

void BasalDose_DoseTimingInitiate(void);

/** Function: BasalDose_DoseTimingEnable()
 *  
 *  The function is called after BasalDose_DoseTimingInitiate().
 *  Function is used to enable TIMER0 IRQ Handler.
 *  
 *  @param void: void
 *  @return void: void
 */

void BasalDose_DoseTimingEnable(void);

/** Function: BasalDose_DoseTimingDisable()
 *  
 *  Function is used to disable TIMER0 IRQ Handler.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void BasalDose_DoseTimingDisable(void);

/** Function: BasalDose_DoseTimingReset()
 *  
 *  Function is used to reset current TIMER0 counter.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void BasalDose_DoseTimingReset(void);

/** Function: BasalDose_DoseAmountInitiate()
 * 
 *  The function is called at the beginning of the main function in Control.c.
 *  Function is used initialize Timer1, but not start counting.
 */

void BasalDose_DoseInitiate(void);

/** Function: BasalDose_DoseEnable().
 * 
 *  Called when MRO interrupt on Timer0.
 *  It disables Timer0, enables and resets Timer1.
 *	
 *	@param void: void
 *	@return void: void
 */

void BasalDose_DoseEnable(void);

/** Function: BasalDose_DoseDisable()
 *  
 *  The function is called after StepperMotor_StepForward() and StepperMotor_StepBackward().
 *  Function is used to disable TIMER1 IRQ Handler.
 *  
 *  @param void: void
 *  @return void: void
 */

void BasalDose_DoseDisable(void);

/** Function: BasalDose_DoseReset()
 *  
 *  The function is called after StepperMotor_StepForward() and StepperMotor_StepBackward().
 *  Function is used to disable TIMER1 IRQ Handler.
 *  
 *  @param void: void
 *  @return void: void
 */

void BasalDose_DoseReset(void);

/** Function: TIMER0_IRQHandler()
 *  
 *  The handler for Timer0 interrupt.
 *  
 *  @param void: void
 *  @return void: void
 */
void TIMER0_IRQHandler(void);

/** Function: TIMER1_IRQHandler()
 *  
 *  The handler for Timer1 interrupt.
 *  
 *  @param void: void
 *  @return void: void
 */

void TIMER1_IRQHandler(void);

#endif /* BASALDOSE_H_ */
