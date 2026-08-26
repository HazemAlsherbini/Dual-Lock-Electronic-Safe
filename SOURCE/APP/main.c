

#include "../../INCLUDE/LIB/BIT_MATH.h"
#include "../../INCLUDE/LIB/STD_TYPES.h"

#include "../../INCLUDE/MCAL/DIO/DIO_INTERFACE.h"
#include "../../INCLUDE/HAL/LCD/LCD_INTERFACE.h"
#include "../../INCLUDE/HAL/KEYPAD/KEYPAD_INTERFACE.h"
#include "../../INCLUDE/MCAL/ADC/ADC_INTERFACE.h"


#include <util/delay.h>
#include <stdbool.h>

volatile u8 G_u8ForceCloseFlag = 0;

void APP_voidCloseSafe(void)
{
	G_u8ForceCloseFlag = 1;
}

int main(void)
{
	u8 L_u8EnteredPassword[4];
    u8 L_u8DialValue = 0;
    u8 L_u8LockStatus = 0;
	u8 L_u8ErrorCounter = 0;
    u8 L_u8ButtonState = 1;


	MDIO_voidInit();     /* initialize DIO before asking LCD/KEYPAD to work */
	HLCD_voidInit();     /* initialize LCD */
	HKEYPAD_voidInit();  /* initialize KEYPAD */
	MADC_voidInit();	 /* initialize ADC */

	// Potentiometer PIN
	MDIO_voidSetPinDirection(PORTA, PIN0, DIO_INPUT);
	MDIO_voidSetPinValue(PORTA, PIN0, DIO_FLOATING);

	// LED PIN
	MDIO_voidSetPinDirection(PORTA, PIN1, DIO_OUTPUT);
	MDIO_voidSetPinValue(PORTA, PIN1, DIO_LOW);

    // Buzzer PIN
    MDIO_voidSetPinDirection(PORTA, PIN2, DIO_OUTPUT);
    MDIO_voidSetPinValue(PORTA, PIN2, DIO_LOW);

    //Alarm LED PIN
	MDIO_voidSetPinDirection(PORTA, PIN4, DIO_OUTPUT);
	MDIO_voidSetPinValue(PORTA, PIN4, DIO_LOW);

    while(1)
    {
    	MDIO_voidSetPinValue(PORTA, PIN1, DIO_LOW);

    		while (L_u8ErrorCounter == 3)
    		{
			MDIO_voidSetPinValue(PORTA, PIN2, DIO_HIGH);
			MDIO_voidSetPinValue(PORTA, PIN4, DIO_HIGH);

			HLCD_voidClearDisplay();
			HLCD_voidSendString((u8 *) "SYSTEM LOCKED!");
			_delay_ms(1500);

			HLCD_voidClearDisplay();
			HLCD_voidSendString((u8 *) "MASTER PASS:");
			_delay_ms(2500);
			HLCD_voidClearDisplay();

			APP_voidGetPasswordFromUser(L_u8EnteredPassword , false);

			if (APP_u8VerifyMasterPassword(L_u8EnteredPassword) == 1)
			{
				MDIO_voidSetPinValue(PORTA, PIN2, DIO_LOW);
				MDIO_voidSetPinValue(PORTA, PIN4, DIO_LOW);
				L_u8ErrorCounter = 0;

				HLCD_voidClearDisplay();
				HLCD_voidSendString((u8 *) "ALARM OFF");
				_delay_ms(1500);
			}
			else
			{
				HLCD_voidClearDisplay();
				HLCD_voidSendString((u8 *) "WRONG MASTER!");
				_delay_ms(1500);
			}
		}

    	// Display welcome screen  and ask the user to enter password or press '*' to change password.
    	APP_voidDisplayWelcomeScreen();

    	// get pass or '*'
    	APP_voidGetPasswordFromUser(L_u8EnteredPassword , false);

    	// user press '*'
    	if (L_u8EnteredPassword[0] == '*')
        {
             APP_voidChangePassword();
        }

    	// Otherwise, the user entered  a normal 4-digit password.
        else
        {
           //Get current dial value

            L_u8DialValue = APP_u8GetDialValue();

             // Verify password + dial

            L_u8LockStatus =  APP_u8VerifyDualLock(  L_u8EnteredPassword, L_u8DialValue); // i set verifying function to return 0 or 1 in APP.c

             //Correct password + correct dial

            if (L_u8LockStatus == 1)
            {
                L_u8ErrorCounter = 0;
            	// Turn on the LED
            	MDIO_voidSetPinValue(PORTA, PIN1, DIO_HIGH);

                HLCD_voidClearDisplay();
                HLCD_voidSendString((u8 *)"ACCESS APPROVED");
            	HLCD_voidGoToPos(ROW2, col1);
                HLCD_voidSendString((u8 *)"THE SAFE IS OPEN");
                _delay_ms(2000);

                HLCD_voidClearDisplay();
                HLCD_voidSendString((u8 *)"IT'LL BE CLOSED");

                u16 CloseTime = 20;
                while(CloseTime != 0)
                {
                	HLCD_voidGoToPos(ROW2, col1);
                	HLCD_voidSendString((u8 *)"  IN ");
                	HLCD_voidDisplayNumberSigned((s32)(CloseTime) );
                	HLCD_voidSendString((u8 *)" SECs");

                	_delay_ms(1000);
                	CloseTime--;
                }

                HLCD_voidClearDisplay();
                HLCD_voidSendString((u8 *)"SAFE IS CLOSED");
            	_delay_ms(2000);

            }

             // Wrong password or wrong dial

            else
            {
            	L_u8ErrorCounter++;

                HLCD_voidClearDisplay();
                HLCD_voidSendString((u8 *)" ACCESS DENIED");
                HLCD_voidGoToPos(ROW2, col1);
                HLCD_voidSendString((u8 *)"   TRY AGAIN");
                _delay_ms(2500);
            }
        }
    }
    return 0;
}
