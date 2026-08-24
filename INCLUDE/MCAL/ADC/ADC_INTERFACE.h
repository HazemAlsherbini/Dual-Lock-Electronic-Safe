/*
 * ADC_INTERFACE.h
 *
 *  Created on: Aug 24, 2026
 *      Author: zom22
 */

#ifndef INCLUDE_MCAL_ADC_ADC_INTERFACE_H_
#define INCLUDE_MCAL_ADC_ADC_INTERFACE_H_





// ADC Channels Macros (Choosing the bit we read from)
#define ADC_CHANNEL_0    PIN0
#define ADC_CHANNEL_1    PIN1
#define ADC_CHANNEL_2    PIN2
#define ADC_CHANNEL_3    PIN3
#define ADC_CHANNEL_4    PIN4
#define ADC_CHANNEL_5    PIN5
#define ADC_CHANNEL_6    PIN6
#define ADC_CHANNEL_7    PIN7


// Function Prototypes
void MADC_voidInit(void);
u16 MADC_u16GetChannelReading(u8 A_u8Channel);

#endif /* INCLUDE_MCAL_ADC_ADC_INTERFACE_H_ */
