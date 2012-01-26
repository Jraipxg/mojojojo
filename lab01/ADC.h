/*
	File Name: ADC.h
	Authors: Joshua James and Mohit Taneja
	Initial Creation Date: 10/11/11
	Description: ADC Driver
	Lab Number: 7
	TA: Sundeep
	Date of last revision: 10/11/11
	Hardware configuration: 
*/

#ifndef ADC_H
#define ADC_H

#include "utils.h"

#define UPDATE_RATE 20			//hz
#define ADC_BUFFER_SIZE 100

extern volatile uint32_t adcBuffer[ADC_BUFFER_SIZE];

extern void ADC_init(void);
extern uint32_t ADC_getValue(void);
extern uint32_t ADC_getSize(void);
extern uint32_t ADC_getStart(void);
extern uint32_t ADC_getLatest(void);

#endif
