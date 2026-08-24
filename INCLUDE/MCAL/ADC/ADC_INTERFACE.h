/*
 * ADC_INTERFACE.h
 *
 *  Created on: Aug 24, 2026
 *      Author: zom22
 */

#ifndef INCLUDE_MCAL_ADC_ADC_INTERFACE_H_
#define INCLUDE_MCAL_ADC_ADC_INTERFACE_H_

/*
 * Voltage Reference Selection
 * Options:
 * 1- ADC_AREF      (External Reference)
 * 2- ADC_AVCC      (5V from AVCC pin)
 * 3- ADC_INTERNAL  (Internal 2.56V)
 */
typedef enum
{
	ADC_AREF = 0,
	ADC_AVCC = 1,
	ADC_RESERVED = 2,
	ADC_INTERNAL= 3
}ADC_VOLTAGE_REFERENCE;

#define ADC_VREF   ADC_AVCC

/*
 * ADC Prescaler Selection
 * Options:
 * ADC_PRESCALER_2
 * ADC_PRESCALER_4
 * ADC_PRESCALER_8
 * ADC_PRESCALER_16
 * ADC_PRESCALER_32
 * ADC_PRESCALER_64
 * ADC_PRESCALER_128
 */
typedef enum
{
	ADC_PRESCALER_2 = 1,
	ADC_PRESCALER_4 = 2,
	ADC_PRESCALER_8 = 3,
	ADC_PRESCALER_16 = 4,
	ADC_PRESCALER_32 = 5,
	ADC_PRESCALER_64 = 6,
	ADC_PRESCALER_128 = 7
}ADC_PRESCALAR;

// Function Prototypes
void MADC_voidInit(void);
u16 MADC_u16GetChannelReading(u8 A_u8Channel);

#endif /* INCLUDE_MCAL_ADC_ADC_INTERFACE_H_ */
