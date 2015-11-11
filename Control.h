/**
 *  StepperMotor.h
 *
 *  Created on: Nov 11, 2015
 *      Author: mfeist
 */
 
#ifndef CONTROL_CONTROL_H_
#define CONTROL_CONTROL_H_

#include "lpc17xx.h" // Device header

// Create bool
typedef enum {false, true} bool;

#define SYRINGE_LENGTH 400
#define BASAL_STEPS 50
#define BOLUS_STEPS 200

/** Function Control_IsSyringeEmpty()
 *  
 *  Function is called in the TIMER1 IRQ Handler.
 *  The function checks if the syringe is empty.
 *  If the syringe is not empty, the pump will inject
 *  the user.  If the syringe is empty, the pump will
 *  retract the syringe.
 *  
 *  @param void: void
 *  @return bool: true or false
 */

bool Control_IsSyringeEmpty(void);

/** Function Control_DosageAmount()
 *  
 *  Function is called in the TIMER0 IRQ Handler
 *  as well as the External Interrupt 3 IRQ Handler.
 *  The function assings the amount of steps that the motor
 *  will take to inject insulin depending on whether a 
 *  basal or bolus injection will occur.
 *  
 *  @param uin32_t: unsigned integer 32-bit
 *  @return void: void
 */

void Control_DosageAmount(uint32_t amount);

#endif /* CONTROL_CONTROL_H_ */
