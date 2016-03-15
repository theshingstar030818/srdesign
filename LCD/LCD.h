 /**
 *  LCD.h
 *
 *  Created on: Dec 16, 2015
 *      Author: sle
 */
 
#ifndef LCD_LCD_H_
#define LCD_LCD_H_

#include "..\Control.h"

/** Function LCD_Initiate()
 *
 *  Initializes LCD screen with Font Size, Background, and
 *  foreground colors then clears out screen.
 *
 *  @param void: void 
 *  @return void: void
 */

void LCD_Initiate(void);

/** Function LCD_UpdateScreenStatus()
 *
 *  Updates the LCD with current status of the controller.
 *
 *  @param void: void 
 *  @return void: void
 */

void LCD_UpdateScreenStatus(void);

/** Function LCD_UpdateScreenState()
 *
 *  Updates the LCD with current state of the controller.
 *
 *  @param void: void 
 *  @return void: void
 */
 
void LCD_UpdateScreenState(void);

/** Function LCD_UpdateScreenInsulin()
 *
 *  Updates the LCD with current insulin count.
 *
 *  @param void: void 
 *  @return void: void
 */

void LCD_UpdateScreenInsulin(void);

/** Function LCD_BasalRate()
 *
 *  Allows user to select Basal profile.
 *
 *  @param void: void 
 *  @return void: void
 */
 
 void LCD_SetUpCommon(void);
 
 void LCD_Options(BaseDisplay current);

#endif /* LCD_LCD_H_ */
