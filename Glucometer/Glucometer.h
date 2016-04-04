/**
 *  Glucometer.h
 *
 *  Created on: Jan 30, 2016
 *      Author: sle
 */
 
#ifndef GLUCOMETER_GLUCOMETER_H_
#define GLUCOMETER_GLUCOMETER_H_

/** Glucometer_Initiate()
 *
 *  Initialize ADC.
 *
 *  @param void: void
 *  @return void: void
 */
 
void Glucometer_Initiate(void);

/** Glucometer_StartConversion()
 *
 *  Initiate a conversion on the ADC.
 *
 *  @param void: void
 *  @return void: void
 */
 
void Glucometer_StartConversion(void);

/** Glucometer_GetADCReading()
 *
 *  Return the last successful ADC reading.
 *
 *  @param void: void
 *  @return int32_t: Glucometer_Last - on success return reading otherwise -1
 */

int32_t Glucometer_GetADCReading(void);

/** Glucometer_ConversionDone()
 *
 *  Return whether or not a new conversion has completed since last read.
 *
 *  @param void: void
 *  @return int32_t: Glucometer_Done - on success return 0 otherwise -1
 */
 
int32_t Glucometer_ConversionDone(void);

/** Glucometer_GetReadings()
 *
 *  Assign raw ADC reading and pH conversion to the structure passed in.
 *
 *  @param ProfileOptions*: current - global ProfileOptions for user
 *  @return void: void
 */
 
void Glucometer_GetReadings(ProfileOptions* current);

/** ADC_IRQHandler()
 *
 *  Interrupt to signal that new ADC reading is available, extract
 *	reading for later use.
 *
 *  @param void: void
 *  @return void: void
 */
 
void ADC_IRQHandler(void);

#endif /* GLUCOMETER_GLUCOMETER_H_ */
