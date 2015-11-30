/**
 *  Control.h
 * 
 *  Created on: Nov 11, 2015
 *      Author: mfeist
 */

#ifndef CONTROL_CONTROL_H_
#define CONTROL_CONTROL_H_

#include "lpc17xx.h" // Device header

// Create bool enum
typedef enum {false, true} bool;
// Create state machine enum
typedef enum {Basal, Bolus, Backward, None} status;

#define SYRINGE_LENGTH 400
#define BASAL_STEPS 50
#define BOLUS_STEPS 200

/** Function Control_LEDInitiate()
 *
 *  Function is called in the main loop to initialize the LED pins,
 *  LPC_GPIO1 pins P1.28-P1.31 as output.
 *
 *  @param void: void 
 *  @return void: void
 */

void Control_LEDInitiate(void);

/** Function Control_ClockInitiate()
 *
 *  Function is called in the main loop to initialize clock.
 *	Powers up Timer0 and Timer1 and sets PCLK = CCLK
 *
 *  @param void: void 
 *  @return void: void
 */
 
void Control_ClockInitiate(void);

#endif /* CONTROL_CONTROL_H_ */
