/*
 * ADC_PRIVATE.h
 *
 *  Created on: Aug 24, 2026
 *      Author: zom22
 */

#ifndef INCLUDE_MCAL_ADC_ADC_PRIVATE_H_
#define INCLUDE_MCAL_ADC_ADC_PRIVATE_H_

// 1. ADC Multiplexer Selection Register
#define ADMUX_REG    (*(volatile u8*)0x27)

// 2. ADC Control and Status Register A
#define ADCSRA_REG   (*(volatile u8*)0x26)

// 3. ADC Data Registers (The final result register)
#define ADCH_REG     (*(volatile u8*)0x25)
#define ADCL_REG     (*(volatile u8*)0x24)

// OPTIONAL: to read the 10 bits in a 16 bits in one time
#define ADC_DATA_REG (*(volatile u16*)0x24)

#endif /* INCLUDE_MCAL_ADC_ADC_PRIVATE_H_ */
