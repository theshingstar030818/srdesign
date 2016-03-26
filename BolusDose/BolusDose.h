/**
 *  BolusDose.h
 *
 *  Created on: Aug 31, 2015
 *      Author: sle
 */

#ifndef BOLUSDOSE_H_
#define BOLUSDOSE_H_ 

/** Function:  BolusDose_DoseInitiate()
 * 
 *  Used to set P2.10 (INT0 button) as an falling-edge 
 *  external interrupt input that is mapped to EINT3.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void BolusDose_DoseInitiate(void);

void BolusDose_AdministerBolus(void);

/** Function: EINT3_IRQHandler()
 *
 *  The interrupt handler for the external interrupt connected 
 *  to pin P2.10. Generates a bolus dose.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void EINT3_IRQHandler(void);

#endif /* BOLUSDOSE_H_ */
