/**
 *  Glucometer.h
 *
 *  Created on: Jan 30, 2016
 *      Author: sle
 */

/** Glucometer_Initiate()
 *
 *  Initialize ADC.
 *
 *  @param void: void
 *  @return void: void
 */
 
void Glucometer_Initiate(void);

/** Glucometer_GetADCReading()
 *
 *  Get ADC value and convert.
 *
 *  @param void: void
 *  @return uint32_t: temp
 */
 
void Glucometer_StartConversion(void);

int32_t Glucometer_GetADCReading(void);

int32_t Glucometer_ConversionDone(void);

uint32_t Glucometer_GetPH(void);