/*
 * BasalDose.h
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#ifndef BASALDOSE_H_
#define BASALDOSE_H_


/* Function:  BasalDose_DoseTimingInitiate()
 *
 * Must be called at the beggining of the main method.
 * Function is used to set the GPIO pins 28, 29, 30, 31 to output,
 * then masks the bits 0,...,27 to maintain integrity of those pins.
 * Currently, set up and enables Timer0.
 */

void BasalDose_DoseTimingInitiate(void);

/* Function: BasalDose_DoseEnable().
 *
 * Called when MRO interrupt on Timer0.
 * Function is used to enable Timer1.
 * It clears the MRO interrupt flag.
 * Toggles LED on pin P1.29.
 */

void BasalDose_DoseEnable(void);

/* Function: BasalDose_DoseAmountInitiate()
 *
 * Called at the end of BasalDose_DoseAmountInitiate().
 * Function is used to set up Timer1.
 */

void BasalDose_DoseAmountInitiate(void);

/* Function: BasalDose_DoseInject()
 *
 * Called when MRO interrupt on Timer1.
 * Function is used to set up but not initialize Timer1.
 */

void BasalDose_DoseInject(void);

#endif /* BASALDOSE_H_ */
