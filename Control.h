/**
 *  Control.h
 * 
 *  Created on: Nov 11, 2015
 *      Author: mfeist
 */

#ifndef CONTROL_CONTROL_H_
#define CONTROL_CONTROL_H_

#include <stdbool.h>
#include "lpc17xx.h"     // Device header
#include "Board_GLCD.h"  // Board Support : Graphic LCD
#include "GLCD_Config.h" // Board Support : Graphic LCD
#include "Board_Joystick.h" // Board Support : Joystick

#define SYRINGE_LENGTH 5000
#define BASAL_STEPS 250
#define BOLUS_STEPS 1000
#define WARNING_20 (SYRINGE_LENGTH * .8)
#define WARNING_10 (SYRINGE_LENGTH * .9)
#define WARNING_05 (SYRINGE_LENGTH * .95)

// Create state machine enum
typedef enum {None_Status, Basal_Status, Bolus_Status, Backward_Status, Wait_Status} STATUS;
typedef enum {None_State, Administration_State, Empty_State, Full_State} STATE;
typedef enum {None_Remaining, Basal_Remaining, Bolus_Remaining} REMAINING;

/** Function Control_LEDInitiate()
 *
 *  Function is called in the main loop to initialize the LED pins,
 *  Set pins P1.28, P1.29, P1.31 as output.
 *  Set pins P2.2, P2.3 as output.
 *
 *  @param void: void 
 *  @return void: void
 */

void Control_LEDInitiate(void);

/** Function Control_LEDClearAdmin()
 *
 *	Clear out LEDs P1.28, P1.29, P1.31, P2.2, P2.3
 *	used as Basal, Bolus, and Backward indicators
 *
 *  @param void: void 
 *  @return void: void
 */
 
void Control_LEDClearAdmin(void);

/** Function Control_LEDClearAll()
 *
 *	Clear out LEDs P1.28, P1.29, P1.31, P2.2, P2.3, P2.4, P2.5, P2.6
 *	used as Basal, Bolus, and Backward indicators
 *
 *  @param void: void 
 *  @return void: void
 */
 
void Control_LEDClearAll(void);

/** Function Control_ClockInitiate()
 *
 *  Function is called in the main loop to initialize clock.
 *  Powers up Timer0 and Timer1 and sets PCLK = CCLK.
 *
 *  @param void: void 
 *  @return void: void
 */
 
void Control_ClockInitiate(void);

/** Function Control_DosageReset()
 *
 *  Function is called in the main loop and StepperMotor_StepForward.
 *
 *  @param void: void 
 *  @return void: void
 */
 
void Control_DosageReset(void);

#endif /* CONTROL_CONTROL_H_ */
