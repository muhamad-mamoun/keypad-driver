/*
===========================================================================================================
Author       : Mamoun
Module       : Keypad
File Name    : keypad.h
Date Created : Oct 15, 2022
Description  : Header file for the keypad driver.
===========================================================================================================
*/


#ifndef KEYPAD_H_
#define KEYPAD_H_

/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "std_types.h"

/*===========================================================================================================
                                < Definitions and Static Configurations >
===========================================================================================================*/

//#define STANDARD_KEYPAD

#define KEYPAD_NUMBER_OF_ROWS                   (4u)
#define KEYPAD_NUMBER_OF_COLUMNS                (4u)

#if((KEYPAD_NUMBER_OF_ROWS != 4)|((KEYPAD_NUMBER_OF_COLUMNS != 3)&&(KEYPAD_NUMBER_OF_COLUMNS != 4)))
#error "Invalid Keypad Configurations"
#endif

#define KEYPAD_ROWS_PORT_ID                     (PORTA_ID)
#define KEYPAD_COLUMNS_PORT_ID                  (PORTA_ID)
#define KEYPAD_FIRST_ROW_PIN_ID                 (PIN0_ID)
#define KEYPAD_FIRST_COLUMN_PIN_ID              (PIN4_ID)

#define KEYPAD_BUTTON_PRESSED                   (HIGH)
#define KEYPAD_BUTTON_RELEASED                  (LOW)

#define ZERO_ASCII_VALUE                        (48u)
#define ENTER_ASCII_VALUE                       (13u)

/*===========================================================================================================
                                         < Functions Prototypes >
===========================================================================================================*/


/*===========================================================================================================
 * [Function Name] : KEYPAD_getPressedKey
 * [Description]   : Rounding on the rows and columns and return the value of the pressed key.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the value of the pressed key.
 ==========================================================================================================*/
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
