/**
 *  Glucometer.h
 *
 *  Created on: Jan 30, 2016
 *      Author: sle
 */

/** Glucometer_Initiate()
 *
 *  Initialize ADC
 *
 *  @param void: void
 *  @return void: void
 */
 
void Glucometer_Initiate(void);

/** Glucometer_GetValue()
 *
 *  Get ADC value and convert.
 *
 *  @param void: void
 *  @return void: void
 */
 
uint32_t Glucometer_GetADCReading(void);

uint32_t Glucometer_GetADCResolution(void);
