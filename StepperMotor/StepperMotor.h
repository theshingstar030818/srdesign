/**
 *  StepperMotor.h
 *
 *  Created on: Sep 8, 2015
 *      Author: sle
 */

#ifndef STEPPERMOTOR_STEPPERMOTOR_H_
#define STEPPERMOTOR_STEPPERMOTOR_H_

/** Function: StepperMotor_Initiate()
 * 
 *  Set pins P0.0 P0.1, P0.2, P0.3 as output.
 *  Initializes globals used to keep track of current 
 *  state of stepper motor and syringe.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void StepperMotor_Initiate(void);

/** Function: StepperMotor_StepForward()
 * 
 *  Uses the StepperMotor_CurrentPosition to determine the
 *  next half-step in the forward motor sequence and assigns it.
 *  Then checks various status variables to see if any further action is required.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void StepperMotor_StepForward(void);

/** Function: StepperMotor_StepBackward()
 * 
 *  Uses the StepperMotor_CurrentPosition to determine the
 *  next half-step in the motor backward sequence and assigns it.
 *  Then checks to see if the current retraction has finished.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void StepperMotor_StepBackward(void);

/** Function: StepperMotor_SpinInitiate()
 * 
 *  Sets up and enables Timer1.
 *
 *  @param void: void
 *  @return void: void
 */

void StepperMotor_SpinInitiate(void);

/** Function: StepperMotor_SpinEnable()
 * 
 *  Function is used to enable Timer1 counter,
 *  then disables and resets Timer0.
 *	
 *  @param void: void
 *  @return void: void
 */

void StepperMotor_SpinEnable(void);

/** Function: StepperMotor_SpinDisable()
 *  
 *  Function is used to disable and reset Timer1.
 *  
 *  @param void: void
 *  @return void: void
 */

void StepperMotor_SpinDisable(void);


/** Function: TIMER1_IRQHandler()
 *  
 *  Depending on the GlobalStatus, administer dosages accordingly.
 *  
 *  @param void: void
 *  @return void: void
 */

void TIMER1_IRQHandler(void);

#endif /* STEPPERMOTOR_STEPPERMOTOR_H_ */
