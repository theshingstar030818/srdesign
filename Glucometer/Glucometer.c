/**
 *  Glucometer.c
 *
 *  Created on: Jan 30, 2016
 *      Author: sle
 */
 
#include "..\Control.h"

static volatile uint16_t AD_last;
static volatile uint8_t  AD_done;
 
void Glucometer_Initiate(void)
{
	LPC_SC->PCONP |= (1 << 12) | (1 << 15);
	
	LPC_PINCON->PINSEL1 &= ~(3 << 14);
	LPC_PINCON->PINSEL1 |= (1 << 14);
	
	LPC_ADC->ADCR = (1 << 0) | (4 << 8) | (1 << 21);
	
	LPC_ADC->ADINTEN =  ( 1 <<  8);
	
	NVIC_EnableIRQ(ADC_IRQn);
}

void Glucometer_StartConversion(void) 
{
  LPC_ADC->ADCR &= ~( 7 << 24);
  LPC_ADC->ADCR |=  ( 1 << 24);
}

int32_t Glucometer_GetADCReading(void)
{
	if (AD_done)
	{
    AD_done = 0;
    return AD_last;
  }
  return -1;
}

int32_t Glucometer_ConversionDone (void)
{
  return (AD_done ? 0 : -1);
}

void ADC_IRQHandler(void) {
  volatile uint32_t adstat;

  adstat = LPC_ADC->ADSTAT;

  AD_last = (LPC_ADC->ADGDR >> 4) & 0xFFF;

  AD_done = 1;
}
