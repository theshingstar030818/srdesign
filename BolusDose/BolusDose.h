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

/** Function: BolusDose_AdministerBolus()
 *
 *  The function is called when the flag is set by external interrupt.
 *	The function is set up since there are two functions trying to call SSP.
 *  
 *  @param void: void
 *  @return void: void
 */

void BolusDose_AdministerBolus(void);

/** Function: EINT3_IRQHandler()
 *
 *  The interrupt handler for the external interrupt connected 
 *  to pin P2.10. Sets flag for bolus dose selection.
 *  Ensures no overdose.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void EINT3_IRQHandler(void);

#endif /* BOLUSDOSE_H_ */
