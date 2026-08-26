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

// Correct pass array
static u8 Correct_Password[4] = {'1', '2', '3', '4'};
static u8 Local_u8Master[4] = {'9', '9', '9', '9'};

// Read the potentiometer reading  by ADC and change the range of digital to 0-99 to be easy to deal with
u8 APP_u8GetDialValue()
{
	u16 L_u16ADCReading = 0; // to take ADC reading
	u8 L_u8DialValue = 0; // store final value of ADC after change

	//call ADC to read voltage at channel 0 and return digital value 0-1023
	L_u16ADCReading = MADC_u16GetChannelReading(ADC_CHANNEL_0);

	// mapping ADC value (0 -> 1023)
	// to Dial value (0 -> 99)
	// UL --> Unsigned Long  32-bit
	L_u8DialValue = (u8) (((u32) L_u16ADCReading * 99UL) / 1023UL); // u32 -> casting to prevent overflow    (new/old)*reading

	return L_u8DialValue; //return final value
}

void APP_voidDisplayWelcomeScreen(void)
{
    HLCD_voidClearDisplay();

    HLCD_voidSendString((u8 *)"WELCOME!");

    _delay_ms(1000);

    HLCD_voidClearDisplay();

    HLCD_voidSendString((u8 *)"Press * to");
    HLCD_voidGoToPos(ROW2, col1);
    HLCD_voidSendString((u8 *)"Change Password");

    _delay_ms(1500);

    HLCD_voidClearDisplay();

    HLCD_voidSendString((u8 *)"Enter Password:");

}

// Get Password From User
void APP_voidGetPasswordFromUser(u8* A_u8PasswordArray)
{
    u8 L_u8PressedKey = KEYPAD_NOT_PRESSED; // No pressed key right now
    u8 L_u8EnteredNumbersCounter = 0;

    HLCD_voidGoToPos(ROW2, col1);

    while (L_u8EnteredNumbersCounter < 4)
        {
            L_u8PressedKey = HKEYPAD_u8GetPressedKey();

             // First key is '*'
             // This means that the user wants to change the password.
            if ((L_u8PressedKey == '*') && (L_u8EnteredNumbersCounter == 0)) //first key is *
            {
                A_u8PasswordArray[0] = '*'; // Flag that he want to change password to use it in main

                return;
            }


              //Normal password input   Only numbers from 0 to 9 are accepted.
            else if ((L_u8PressedKey >= '0') && (L_u8PressedKey <= '9'))
            {
                A_u8PasswordArray[L_u8EnteredNumbersCounter] = L_u8PressedKey; // counter is the index of the array

                HLCD_voidSendData('*'); // for safety

                L_u8EnteredNumbersCounter++;

                if (L_u8EnteredNumbersCounter == 4) // after entering 4 numbers
                {
                    _delay_ms(500);

                    HLCD_voidClearDisplay();

                    HLCD_voidSendString((u8 *)"Password Stored!");

                    _delay_ms(700);
                }
            }
        }
}



//-------------------------------------------------------------------------------
u8 APP_u8VerifyMasterPassword(u8* A_u8EnteredPass)
{

    u8 Local_u8Iterator = 0;

    for (Local_u8Iterator = 0; Local_u8Iterator < 4; Local_u8Iterator++)
    {
        if (A_u8EnteredPass[Local_u8Iterator] != Local_u8Master[Local_u8Iterator])
        {
            return 0;
        }
    }

    return 1;
}
//-----------------------------------------------------------------------------


// Arguments are pointer of the input function and the pass array
u8 APP_u8VerifyDualLock(u8* A_u8EnteredPass, u8 A_u8DialValue)
{
	// LET THE enterd pass to be correct at first
	u8 Local_u8PassIsCorrect = 1;

	//A COUNTER
	u8 Local_u8Iterator = 0;

	//Checking loop
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


// Change Password
void APP_voidChangePassword(void)
{
    u8 L_u8OldPassword[4];
    u8 L_u8NewPassword[4];

    u8 L_u8DialValue = 0; // i make it to compare it with the current dial value
    u8 L_u8OldPasswordIsCorrect = 0; // flag to store wither password is correct or no


     //Step 1:
     //Ask the user to enter the old password

    HLCD_voidClearDisplay();
    HLCD_voidSendString((u8 *)"Old Password:");

    HLCD_voidGoToPos(ROW2, col1);

    APP_voidGetPasswordFromUser(L_u8OldPassword);



     // Step 2:
     // Get the current dial value

    L_u8DialValue = APP_u8GetDialValue();



     // Step 3:
     // Verify old password + correct dial

    L_u8OldPasswordIsCorrect = APP_u8VerifyDualLock(L_u8OldPassword, L_u8DialValue);



     //Step 4:
     //If both are correct, allow password change

    if (L_u8OldPasswordIsCorrect == 1)
    {
        HLCD_voidClearDisplay();

        HLCD_voidSendString((u8 *)"Enter New Pass:");

        _delay_ms(500);

        HLCD_voidGoToPos(ROW2, col1);


         // Enter the new password

        APP_voidGetPasswordFromUser(L_u8NewPassword);// recieve new 4 numbers and store them in a new array



         // make the new password to the new password array

        for (u8 k = 0;k < 4; k++)
        {
            Correct_Password[k] =L_u8NewPassword[k];

        }


        HLCD_voidClearDisplay();

        HLCD_voidSendString((u8 *)"Password Changed!");

        _delay_ms(1000);
    }


     //  if entered Old password or dial is incorrect

    else
    {
        HLCD_voidClearDisplay();

        HLCD_voidSendString((u8 *)"Wrong Password");

        HLCD_voidGoToPos(ROW2, col1);

        HLCD_voidSendString((u8 *)"or Wrong Dial");

        _delay_ms(1500);
    }
}

