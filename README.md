# Senior Design Repository
* Our goal is to implement real-time software controller to simulate an Insulin Pump
* The project will be written in C, using many of the pre-defined ARM/LPC17xx libraries
* Hardware:
    * Keil MCB1760UME - Development board used, features Cortex-M3 ARM microprocessor
    * Linear Actuator - Used as the administration mechanism to deliver the insulin
    * Syringe - Used as the holder for the insulin that the Linear Actuator will push

## Primary Goals:
  * Interface MCB Development Board with Linear Actuator using GPIO
  * Interface Linear Actuator with Syringe
  * Implement Functional Basal Dose (*Continuous Dose Over Time*)
  * Implement Functional Bolus Dose (*One Time User-Initiated Dose*)
  * Implement Security Features that apply as specified in [Security Requirements](http://www.ncbi.nlm.nih.gov/pmc/articles/PMC3262707/)

## Secondary Goals:
  * Interface MCB1700 with Continuous Glucose Montior using GPIO
  * Set-up MCB1700 to be able to read/write to micro SD Card
  * Implement Security Features that apply to the additional features
  
## What to include when starting a new Project:
  * GPDMA:
  ** GPIO
