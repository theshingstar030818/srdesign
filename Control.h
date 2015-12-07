/**
 *  Control.h
 * 
 *  Created on: Nov 11, 2015
 *      Author: mfeist
 */

#ifndef CONTROL_CONTROL_H_
#define CONTROL_CONTROL_H_

#include "lpc17xx.h" // Device header

#define SYRINGE_LENGTH 5000
#define BASAL_STEPS 250
#define BOLUS_STEPS 1000

// Create bool enum
typedef enum {false, true} bool;

// Create state machine enum
typedef enum {Basal, Bolus, Backward, None} status;

/** Function Control_LEDInitiate()
 *
 *  Function is called in the main loop to initialize the LED pins,
 *  Set pins P1.28, P1.29, P1.30, P1.31 as output
 *  Set pins P2.2, P2.3 as output
 *
 *  @param void: void 
 *  @return void: void
 */

void Control_LEDInitiate(void);

/** Function Control_LEDClear()
 *
 *	Clear out LEDs P1.28, P1.29, P1.31,
 *	used as Basal, Bolus, and Backward indicators
 *
 *  @param void: void 
 *  @return void: void
 */
 
void Control_LEDClear(void);

/** Function Control_ClockInitiate()
 *
 *  Function is called in the main loop to initialize clock.
 *  Powers up Timer0 and Timer1 and sets PCLK = CCLK
 *
 *  @param void: void 
 *  @return void: void
 */
 
void Control_ClockInitiate(void);

#endif /* CONTROL_CONTROL_H_ */
