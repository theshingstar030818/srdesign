/**
 *  Speaker.h
 *
 *  Created on: Jan 12, 2016
 *      Author: sle
 */

#ifndef SPEAKER_SPEAKER_H_
#define SPEAKER_SPEAKER_H_

#include "..\Control.h"

/** Speaker_Initiate()
 *
 *  Function is called in the main loop to initialize the Speaker pin.
 *  Set pins P0.26 as output.
 *	Initiates Timer3 but not enable.
 *
 *  @param void: void
 *  @return void: void
 */

void Speaker_Initiate(void);

/** Speaker_SetFrequency()
 *
 *  Function is called to set the frequency of the speaker.
 *
 *  @param FREQ: frequency - Sets match register to FREQ value
 *  @return void: void
 */

void Speaker_SetFrequency(FREQ frequency);

/** Function: Speaker_Play()
 *
 *  Function is used to enable Timer3 counter.
 *
 *  @param void: void
 *  @return void: void
 */

void Speaker_Play(void);

/** Function: Speaker_Stop()
 *
 *  Function is used to disable and reset Timer3.
 *
 *  @param void: void
 *  @return void: void
 */

void Speaker_Stop(void);

/** Function: TIMER3_IRQHandler()
 *
 *  Flips power to speaker.
 *
 *  @param void: void
 *  @return void: void
 */

void TIMER3_IRQHandler(void);

#endif /* SPEAKER_SPEAKER_H_ */

