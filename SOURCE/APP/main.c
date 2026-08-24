

#include "../../INCLUDE/LIB/BIT_MATH.h"
#include "../../INCLUDE/LIB/STD_TYPES.h"

#include "../../INCLUDE/MCAL/DIO/DIO_INTERFACE.h"
#include "../../INCLUDE/MCAL/DIO/DIO_PRIVATE.h"
#include "../../INCLUDE/MCAL/DIO/DIO_CFG.h"

#include "../../INCLUDE/HAL/LCD/LCD_INTERFACE.h"


#include "../../INCLUDE/HAL/KEYPAD/KEYPAD_INTERFACE.h"

#include <util/delay.h>

// ADC Directives
#include "../../INCLUDE/MCAL/ADC/ADC_INTERFACE.h"
#include "../../INCLUDE/MCAL/ADC/ADC_PRIVATE.h"
#include "../../INCLUDE/MCAL/ADC/ADC_CFG.h"

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


int main(void)
{
    MDIO_voidInit();     /* initialize dio before asking lcd/keypad to work */
    HLCD_voidInit();     /* initialize lcd */

    u8 L_u8EnteredPassword[4];
    u8 L_u8PressedKey = 0xFF;
    u8 L_u8EnteredNumbersCounter = 0;

    HLCD_voidSendString((u8 *)"Enter Password:");
    HLCD_voidGoToPos(ROW2, col1);
    while (1)
    {
        L_u8PressedKey = HKEYPAD_u8GetPressedKey();

        if ((L_u8PressedKey >= '0') && (L_u8PressedKey <= '9'))

        {
            L_u8EnteredPassword[L_u8EnteredNumbersCounter] = L_u8PressedKey;


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

    return 0;
}
