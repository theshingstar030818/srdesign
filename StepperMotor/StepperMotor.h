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
 *	state of stepper motor and syringe.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void StepperMotor_Initiate(void);

/** Function: StepperMotor_StepForward()
 * 
 *  Uses the StepperMotor_CurrentPosition to determine the
 *	next half-step in the forward motor sequence and assigns it.
 *	Then checks to see if the current dosing has finished.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void StepperMotor_StepForward(void);

/** Function: StepperMotor_StepBackward()
 * 
 *  Uses the StepperMotor_CurrentPosition to determine the
 *	next half-step in the motor backward sequence and assigns it.
 *	Then checks to see if the current retraction has finished.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void StepperMotor_StepBackward(void);

#endif /* STEPPERMOTOR_STEPPERMOTOR_H_ */
