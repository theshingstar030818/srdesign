/*
 * StepperMotor.h
 *
 *  Created on: Sep 8, 2015
 *      Author: sle
 */

#ifndef STEPPERMOTOR_STEPPERMOTOR_H_
#define STEPPERMOTOR_STEPPERMOTOR_H_

/* Function: StepperMotor_Initiate()
 *
 * Must be called at the beginning of the main method.
 * Function is used to set the GPIO0 pins 0, 1, 2, 3 to output,
 * then masks bits 4,...,31 to maintain integrity of those pins.
 * Currently, sets globalPos and currentPos to 0, which are
 * variables that describe where the stepper motor is relative
 * from where it starts.
 */
void StepperMotor_Initiate();

/* Function: StepperMotor_StepForward()
 * TODO: Add description of function
 */
void StepperMotor_StepFoward();

/* Function: StepperMotor_StepBackward()
 * TODO: Add description of function
 */
void StepperMotor_StepBackward();



#endif /* STEPPERMOTOR_STEPPERMOTOR_H_ */
