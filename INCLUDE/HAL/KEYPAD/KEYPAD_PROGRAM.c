/*
 * KEYPAD_PROGRAM.c
 *
 *  Created on: Aug 22, 2026
 *      Author: zom22
 */

#include <util/delay.h>

// Library Directives
#include "../../../INCLUDE/LIB/BIT_MATH.h"
#include "../../../INCLUDE/LIB/STD_TYPES.h"

// DIO Directives
#include "../../../INCLUDE/MCAL/DIO/DIO_INTERFACE.h"
#include "../../../INCLUDE/HAL/KEYPAD/KEYPAD_CFG.h"
#include "../../../INCLUDE/HAL/KEYPAD/KEYPAD_INTERFACE.h"
#include "../../../INCLUDE/HAL/KEYPAD/KEYPAD_PRIVATE.h"

u8 Global_u8ArrOfKeyValues [ROW_NO][COL_NO] = {
		{'1','2','3'},
		{'4','5','6'},
		{'7','8','9'},
		{'*','0','#'}
};

u8 static G_u8RowsArr[ROW_NO] = KEYPAD_ROWS;
u8 static G_u8ColsArr[COL_NO] = KEYPAD_COLS;

void HKEYPAD_voidInit(void)
{
	u8 Local_u8Counter ;

	for(Local_u8Counter = 0 ; Local_u8Counter < ROW_NO ; Local_u8Counter++)
	{
		// Set Rows as Output and HIGH Values
		MDIO_voidSetPinDirection(KEYPAD_PORT ,G_u8RowsArr[Local_u8Counter] , DIO_OUTPUT);
		MDIO_voidSetPinValue(KEYPAD_PORT ,G_u8RowsArr[Local_u8Counter] , DIO_HIGH);
	}

	for(Local_u8Counter = 0 ; Local_u8Counter < COL_NO ; Local_u8Counter++)
	{
		// Set Cols as Intput and Pull UP
		MDIO_voidSetPinDirection(KEYPAD_PORT ,G_u8ColsArr[Local_u8Counter] , DIO_INPUT);
		MDIO_voidSetPinValue(KEYPAD_PORT ,G_u8ColsArr[Local_u8Counter] , DIO_PULLUP);
	}

}

u8 HKEYPAD_u8GetPressedKey(void)
{
	u8 Local_u8RowCounter;
	u8 Local_u8ColCounter;
	u8 Local_u8PinValue = KEYPAD_NOT_PRESSED ;
	u8 Local_u8Flag = Flag_DOWN;
	u8 Local_u8KeyValue = KEYPAD_NOT_PRESSED ;

	for(Local_u8RowCounter = 0 ; Local_u8RowCounter < ROW_NO ; Local_u8RowCounter++)
	{
		MDIO_voidSetPinValue(KEYPAD_PORT ,G_u8RowsArr[Local_u8RowCounter] , DIO_LOW);

		for(Local_u8ColCounter = 0 ; Local_u8ColCounter < COL_NO ; Local_u8ColCounter++)
		{
			Local_u8PinValue = MDIO_PinstatusGetPinValue(KEYPAD_PORT , G_u8ColsArr[Local_u8ColCounter]);

			if(Local_u8PinValue == KEYPAD_PRESSED)
			{
				_delay_ms(KEYPAD_DEBOUNCE_DELAY);

				Local_u8PinValue = MDIO_PinstatusGetPinValue(KEYPAD_PORT , G_u8ColsArr[Local_u8ColCounter]);

				if(Local_u8PinValue == KEYPAD_PRESSED)
				{
					while(Local_u8PinValue == KEYPAD_PRESSED)
					{
						Local_u8PinValue = MDIO_PinstatusGetPinValue(KEYPAD_PORT , G_u8ColsArr[Local_u8ColCounter]);
					}
					Local_u8KeyValue = Global_u8ArrOfKeyValues[Local_u8RowCounter][Local_u8ColCounter];
					Local_u8Flag = Flag_UP;
					break;
				}
			}
		}

		MDIO_voidSetPinValue(KEYPAD_PORT ,G_u8RowsArr[Local_u8RowCounter] , DIO_HIGH);

		if(Local_u8Flag == Flag_UP)
		{
			break;
		}
	}

	return Local_u8KeyValue;
}
