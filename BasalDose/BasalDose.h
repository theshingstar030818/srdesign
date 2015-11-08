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
 *  Function is used to set the GPIO pins 28, 29, 30, 31 to output,
 *  then masks the bits 0,...,27 to maintain integrity of those pins.
 *  Currently, set up and enables Timer0.
 *  
 *  @param void: void
 *  @return void: void
 */

void BasalDose_DoseTimingInitiate(void);

/** Function: BasalDose_DoseTimingEnable()
 *  
 *  The function is called after BasalDose_DoseTimingInitiate()
 *  and at the end of the of the StepperMotor_StepForward() and
 *  StepperMotor_StepBackward().
 *  Function is used to enable TIMER0 IRQ Handler.
 *  
 *  @param void: void
 *  @return void: void
 */

void BasalDose_DoseTimingEnable(void);

/** Function: BasalDose_DoseTimingDisable()
 *  
 *  The funciont is called in BasalDose_DoseInject() as well as BasalDose_RetractSyringe().
 *  Function is used to disable TIMER0 IRQ Handler.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void BasalDose_DoseTimingDisable(void);


/** Function: BasalDose_DoseEnable().
 * 
 *  Called when MRO interrupt on Timer0.
 *  Function is used to enable Timer1.
 *  It clears the MRO interrupt flag.
 *  Toggles LED on pin P1.29.
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

/** Function: BasalDose_DoseAmountInitiate()
 * 
 *  The function is called at the beginning of the main function in Control.c.
 *  Function is used to set up but not initialize Timer1.
 */

void BasalDose_DoseAmountInitiate(void);

/** Function: BasalDose_DoseInject()
 * 
 *  Called when MRO interrupt on Timer1.
 *  Function is used to set up but not initialize Timer1.
 */

void BasalDose_DoseInject(void);

/** Funtion: BasalDose_RetractSyringe()
 *  
 *  The function is called in the TIMER1 IRQ Handler when the check
 *  condition for Control_IsSyringeEmpty() is true.
 *  
 *  @param void: void
 *  @return void: void
 */

void BasalDose_RetractSyringe(void);

/** Function: TIMER0_IRQHandler()
 *  
 *  The function enables Timer0.
 *  
 *  @param void: void
 *  @return void: void
 */
void TIMER0_IRQHandler(void);

/** Function: TIMER1_IRQHandler()
 *  
 *  The function enables Timer1.
 *  
 *  @param void: void
 *  @return void: void
 */

void TIMER1_IRQHandler(void)

#endif /* BASALDOSE_H_ */
