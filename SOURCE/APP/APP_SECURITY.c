#include "../../INCLUDE/LIB/BIT_MATH.h"
#include "../../INCLUDE/LIB/STD_TYPES.h"

// DIO Directives
#include "../../INCLUDE/MCAL/DIO/DIO_INTERFACE.h"
#include "../../INCLUDE/HAL/LCD/LCD_INTERFACE.h"
#include "../../INCLUDE/HAL/KEYPAD/KEYPAD_INTERFACE.h"
#include "../../INCLUDE/MCAL/ADC/ADC_INTERFACE.h"

#include <stdio.h>
#include "APP_SECURITY.h"
#include <util/delay.h>

// correct pass array
static const u8 Correct_Password[4] = {'1', '2', '3', '4'};

u8 APP_u8GetDialValue()
{
	u16 L_u16ADCReading = 0;
	u8 L_u8DialValue = 0;


	L_u16ADCReading = MADC_u16GetChannelReading(ADC_CHANNEL_0);

	// Mapping
	// UL --> Unsigned Long  32-bit
	L_u8DialValue = (u8) (((u32) L_u16ADCReading * 99UL) / 1023UL);

	return L_u8DialValue;
}

void APP_voidDisplayWelcomeScreen(void)
{

    HLCD_voidClearDisplay();
    HLCD_voidSendString((u8 *)"WELCOME!");
    _delay_ms(1000);
    HLCD_voidClearDisplay();
    HLCD_voidSendString((u8 *)"Enter Password:");

}

void APP_voidGetPasswordFromUser(u8* A_u8PasswordArray)
{
    u8 L_u8PressedKey = KEYPAD_NOT_PRESSED;
    u8 L_u8EnteredNumbersCounter = 0;

    HLCD_voidGoToPos(ROW2, col1);
    while (L_u8EnteredNumbersCounter < 4)
    {
        L_u8PressedKey = HKEYPAD_u8GetPressedKey();

        if ((L_u8PressedKey >= '0') && (L_u8PressedKey <= '9'))

        {
        	A_u8PasswordArray[L_u8EnteredNumbersCounter] = L_u8PressedKey;

            HLCD_voidSendData('*');

            L_u8EnteredNumbersCounter++;

            if (L_u8EnteredNumbersCounter == 4)

            {
                _delay_ms(500);
                HLCD_voidClearDisplay();
                HLCD_voidSendString((u8 *)"Password Stored!");
            }
        }
    }
}

// arguments are pointer of the input function and the pass array
u8 APP_u8VerifyDualLock(u8* A_u8EnteredPass, u8 A_u8DialValue)
{
	// LET THE enterd pass to be correct at first
	u8 Local_u8PassIsCorrect = 1;

	//A COUNTER
	u8 Local_u8Iterator = 0;

	//the checking loop
	for (Local_u8Iterator = 0; Local_u8Iterator < 4; Local_u8Iterator++)
	{
		if (A_u8EnteredPass[Local_u8Iterator] != Correct_Password[Local_u8Iterator])
		{
			Local_u8PassIsCorrect = 0;
			break;
		}
	}


	// if the dial and the pass are correct return 1 else 0
	if ((Local_u8PassIsCorrect == 1) && (A_u8DialValue == CORRECT_DIAL_VALUE))
	{
		return 1;
	} else
	{
		return 0;
	}
}

