

#include "../../INCLUDE/LIB/BIT_MATH.h"
#include "../../INCLUDE/LIB/STD_TYPES.h"

#include "../../INCLUDE/MCAL/DIO/DIO_INTERFACE.h"
#include "../../INCLUDE/HAL/LCD/LCD_INTERFACE.h"
#include "../../INCLUDE/HAL/KEYPAD/KEYPAD_INTERFACE.h"
#include "../../INCLUDE/MCAL/ADC/ADC_INTERFACE.h"


#include <util/delay.h>




int main(void)
{
	u8 L_u8EnteredPassword[4];
    u8 L_u8DialValue = 0;
    u8 L_u8LockStatus = 0;

	MDIO_voidInit();     /* initialize DIO before asking LCD/KEYPAD to work */
	HLCD_voidInit();     /* initialize LCD */
	HKEYPAD_voidInit();  /* initialize KEYPAD */
	MADC_voidInit();	 /* initialize ADC */

	// Potentiometer PIN
	MDIO_voidSetPinDirection(PORTA, PIN0, DIO_INPUT);
	MDIO_voidSetPinValue(PORTA, PIN0, DIO_LOW);
	// LED PIN
	MDIO_voidSetPinDirection(PORTA, PIN1, DIO_OUTPUT);

    while(1)
    {

    	// Display welcome screen  and ask the user to enter password or press '*' to change password.
    	APP_voidDisplayWelcomeScreen();

    	// get pass or '*'
    	APP_voidGetPasswordFromUser(L_u8EnteredPassword);

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
                HLCD_voidClearDisplay();

                HLCD_voidSendString((u8 *)"ACCESS APPROVED");

                _delay_ms(1500);
            }

             // Wrong password or wrong dial

            else
            {
                HLCD_voidClearDisplay();

                HLCD_voidSendString((u8 *)"ACCESS DENIED");

                _delay_ms(1500);
            }
        }
    }
    return 0;
}
