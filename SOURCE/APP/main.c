

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

    MDIO_voidInit();     /* initialize DIO before asking LCD/KEYPAD to work */
    HLCD_voidInit();     /* initialize LCD */
    HKEYPAD_voidInit();  /* initialize KEYPAD */


    return 0;
}
