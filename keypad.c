/*
===========================================================================================================
Author       : Mamoun
Module       : Keypad
File Name    : keypad.c
Date Created : Oct 15, 2022
Description  : Source file for the keypad driver.
===========================================================================================================
 */


/*===========================================================================================================
                                               < Includes >
===========================================================================================================*/

#include "gpio.h"
#include "keypad.h"
#include "common_macros.h"

/*===========================================================================================================
                                      < Private Functions Prototypes >
===========================================================================================================*/

#ifndef STANDARD_KEYPAD
#if(KEYPAD_NUMBER_OF_COLUMNS == 3)
/*===========================================================================================================
 * [Function Name] : KEYPAD_4x3_getKeyValue
 * [Description]   : Get the value of the pressed key in 4x3 keypad upon its ID.
 * [Arguments]     : <a_key_id>      -> Indicates to the ID of the pressed key.
 * [return]        : The function returns the value of the pressed key.
 ==========================================================================================================*/
static uint8 KEYPAD_4x3_getKeyValue(uint8 a_key_id);
#endif

#if(KEYPAD_NUMBER_OF_COLUMNS == 4)
/*===========================================================================================================
 * [Function Name] : KEYPAD_4x4_getKeyValue
 * [Description]   : Get the value of the pressed key in 4x4 keypad upon its ID.
 * [Arguments]     : <a_key_id>      -> Indicates to the ID of the pressed key.
 * [return]        : The function returns the value of the pressed key.
 ==========================================================================================================*/
static uint8 KEYPAD_4x4_getKeyValue(uint8 a_key_id);
#endif
#endif /* _STANDARD_KEYPAD_ */

/*===========================================================================================================
                                          < Functions Definitions >
===========================================================================================================*/

/*===========================================================================================================
 * [Function Name] : KEYPAD_getPressedKey
 * [Description]   : Rounding on the rows and columns and return the value of the pressed key.
 * [Arguments]     : The function takes no arguments.
 * [return]        : The function returns the value of the pressed key.
 ==========================================================================================================*/
uint8 KEYPAD_getPressedKey(void)
{
	uint8 pressed_key_id, rows_counter, columns_counter;

	GPIO_setupPinDirection(KEYPAD_ROWS_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+0,INPUT_PIN);
	GPIO_setupPinDirection(KEYPAD_ROWS_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+1,INPUT_PIN);
	GPIO_setupPinDirection(KEYPAD_ROWS_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+2,INPUT_PIN);
	GPIO_setupPinDirection(KEYPAD_ROWS_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+3,INPUT_PIN);

	GPIO_setupPinDirection(KEYPAD_COLUMNS_PORT_ID,KEYPAD_FIRST_COLUMN_PIN_ID+0,INPUT_PIN);
	GPIO_setupPinDirection(KEYPAD_COLUMNS_PORT_ID,KEYPAD_FIRST_COLUMN_PIN_ID+1,INPUT_PIN);
	GPIO_setupPinDirection(KEYPAD_COLUMNS_PORT_ID,KEYPAD_FIRST_COLUMN_PIN_ID+2,INPUT_PIN);
#if(KEYPAD_NUMBER_OF_COLUMNS == 4)
	GPIO_setupPinDirection(KEYPAD_COLUMNS_PORT_ID,KEYPAD_FIRST_COLUMN_PIN_ID+3,INPUT_PIN);
#endif

	while(1)
	{
		for(rows_counter=0; rows_counter<KEYPAD_NUMBER_OF_ROWS; rows_counter++)
		{
			GPIO_setupPinDirection(KEYPAD_ROWS_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+rows_counter,OUTPUT_PIN);
			GPIO_writePin(KEYPAD_ROWS_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+rows_counter,KEYPAD_BUTTON_PRESSED);
			for(columns_counter=0; columns_counter<KEYPAD_NUMBER_OF_COLUMNS; columns_counter++)
			{
				if(GPIO_readPin(KEYPAD_COLUMNS_PORT_ID,KEYPAD_FIRST_COLUMN_PIN_ID+columns_counter) == KEYPAD_BUTTON_PRESSED)
				{
					pressed_key_id = ((rows_counter*KEYPAD_NUMBER_OF_COLUMNS)+columns_counter+1);
#ifdef STANDARD_KEYPAD
					return pressed_key_id;
#else  /* _NOT_STANDARD_KEYPAD_ */
#if(KEYPAD_NUMBER_OF_COLUMNS == 3)
					return KEYPAD_4x3_getKeyValue(pressed_key_id);
#elif(KEYPAD_NUMBER_OF_COLUMNS == 4)
					return KEYPAD_4x4_getKeyValue(pressed_key_id);
#endif /* _KEYPAD_NUM_OF_COLUMNS_ */
#endif /* _STANDARD_KEYPAD_ */
				}
			}
			GPIO_writePin(KEYPAD_ROWS_PORT_ID,KEYPAD_FIRST_ROW_PIN_ID+rows_counter,INPUT_PIN);
		}
	}
}

#ifndef STANDARD_KEYPAD
#if(KEYPAD_NUMBER_OF_COLUMNS == 3)
/*===========================================================================================================
 * [Function Name] : KEYPAD_4x3_getKeyValue
 * [Description]   : Get the value of the pressed key in 4x3 keypad upon its ID.
 * [Arguments]     : <a_key_id>      -> Indicates to the ID of the pressed key.
 * [return]        : The function returns the value of the pressed key.
 ==========================================================================================================*/
static uint8 KEYPAD_4x3_getKeyValue(uint8 a_key_id)
{
	uint8 key_value = 0;
	switch (a_key_id)
	{
	case 10 :
		key_value = '*';
		break;
	case 11 :
		key_value = '0';
		break;
	case 12 :
		key_value = '#';
		break;
	default :
		key_value = (a_key_id+ZERO_ASCII_VALUE);
		break;
	}
	return key_value;
}
#endif

#if(KEYPAD_NUMBER_OF_COLUMNS == 4)
/*===========================================================================================================
 * [Function Name] : KEYPAD_4x4_getKeyValue
 * [Description]   : Get the value of the pressed key in 4x4 keypad upon its ID.
 * [Arguments]     : <a_key_id>      -> Indicates to the ID of the pressed key.
 * [return]        : The function returns the value of the pressed key.
 ==========================================================================================================*/
static uint8 KEYPAD_4x4_getKeyValue(uint8 a_key_id)
{
	uint8 key_value = 0;
	switch (a_key_id)
	{
	case 1 :
		key_value = '7';
		break;
	case 2 :
		key_value = '8';
		break;
	case 3 :
		key_value = '9';
		break;
	case 4 :
		key_value = '%';
		break;
	case 5 :
		key_value = '4';
		break;
	case 6 :
		key_value = '5';
		break;
	case 7 :
		key_value = '6';
		break;
	case 8 :
		key_value = '*';
		break;
	case 9 :
		key_value = '1';
		break;
	case 10 :
		key_value = '2';
		break;
	case 11 :
		key_value = '3';
		break;
	case 12 :
		key_value = '-';
		break;
	case 13 :
		key_value = ENTER_ASCII_VALUE;
		break;
	case 14 :
		key_value = '0';
		break;
	case 15 :
		key_value = '=';
		break;
	case 16 :
		key_value = '+';
		break;
	}
	return key_value;
}
#endif
#endif /* STANDARD_KEYPAD */
