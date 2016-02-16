/**
 *  Speaker.h
 *
 *  Created on: Jan 12, 2016
 *      Author: sle
 */

#ifndef SPEAKER_SPEAKER_H_
#define SPEAKER_SPEAKER_H_

/** Speaker_Initiate()
 *
 *  Function is called in the main loop to initialize the Speaker pin
 *  Set pins P0.26 as output
 *	Initiates Timer3 but not enable
 *
 *  @param void: void
 *  @return void: void
 */

void Speaker_Initiate(void);

/** Speaker_Play()
 *
 *  Function is called to activate the Speaker
 *  Parameter loops dictates how long the Speaker is on for
 *
 *  @param int: loops - number of loops to play sound
 *  @param int: frequency - time in between oscillations
 *  @return void: void
 */

void Speaker_Play(int loops, int frequency);

/** Speaker_Wait()
 *
 *  Function is called to wait between oscillations
 *
 *  @param int: frequency - time in between oscillations
 *  @return void: void
 */

void Speaker_Wait(int frequency);

/** Function: Speaker_Enable()
 *  
 *  Function is used to enable Timer3 counter.
 *  
 *  @param void: void
 *  @return void: void
 */

void Speaker_Enable(void);

/** Function: Speaker_Disable()
 *  
 *  Function is used to disable and reset Timer3.
 *  
 *  @param void: void
 *  @return void: void
 */
 
void Speaker_Disable(void);

/** Function: TIMER3_IRQHandler()
 *  
 *  Sets the timing for the speaker.
 *  
 *  @param void: void
 *  @return void: void
 */

void TIMER3_IRQHandler(void);

#endif /* SPEAKER_SPEAKER_H_ */

