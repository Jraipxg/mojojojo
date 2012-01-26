/*
	File Name: ADC.c
	Authors: Joshua James and Mohit Taneja
	Initial Creation Date: 10/11/11
	Description: ADC Driver
	Lab Number: 7
	TA: Sundeep
	Date of last revision: 10/11/11
	Hardware configuration: 
*/

#include "ADC.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"//for timers
#include "inc/hw_ints.h"	
#include "driverlib/interrupt.h"	

volatile uint32_t adcBuffer[ADC_BUFFER_SIZE];
volatile uint32_t startIndex;
volatile uint32_t size;

uint32_t ADC_getValue(void)
{
    unsigned long ulADC0_Value[1];
	
	ADCProcessorTrigger(ADC0_BASE, 3);
    while(!ADCIntStatus(ADC0_BASE, 3, false));
    ADCSequenceDataGet(ADC0_BASE, 3, ulADC0_Value);
    //Delay(SysCtlClockGet() / 12);
	
	return ulADC0_Value[0];
}

void addValue(uint32_t value)
{
	uint32_t index = startIndex + size;
	if(index >= ADC_BUFFER_SIZE)
	{
		index -= ADC_BUFFER_SIZE;
	}
	
	adcBuffer[index] = value;		//CHANGE MEEEEE!!!!!!!!!!!!!!!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	if(size < ADC_BUFFER_SIZE)
	{
		size++;
	}
	else
	{
		startIndex++;
		if(startIndex == ADC_BUFFER_SIZE)
		{
			startIndex = 0;
		}
	}
}

uint32_t ADC_getSize(void)
{
	return size;
}

uint32_t ADC_getStart(void)
{
	return startIndex;
}

uint32_t ADC_getLatest(void)
{
	uint32_t index;
	if(size == ADC_BUFFER_SIZE)
	{
		if(startIndex == 0)
		{
			index = ADC_BUFFER_SIZE - 1;
		}
		else
		{
			index = startIndex - 1;
		}
	}
	else
	{
		index = size - 1;
	}
	return adcBuffer[index];
}

void Timer0A_Handler(void)
{
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);			// Clear the timer interrupt
	addValue(ADC_getValue());
}

void ADC_init(void)
{
	int i;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
	ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_TIMER, 0);
	
    //
    // Configure step 0 on sequence 3.  Sample the temperature sensor
    // (ADC_CTL_TS) and configure the interrupt flag (ADC_CTL_IE) to be set
    // when the sample is done.  Tell the ADC logic that this is the last
    // conversion on sequence 3 (ADC_CTL_END).  Sequence 3 has only one
    // programmable step.  Sequence 1 and 2 have 4 steps, and sequence 0 has
    // 8 programmable steps.  Since we are only doing a single conversion using
    // sequence 3 we will only configure step 0.  For more information on the
    // ADC sequences and steps, reference the datasheet.
    //
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCIntClear(ADC0_BASE, 3);
	
	for(i = 0; i < ADC_BUFFER_SIZE; i++)
	{
		adcBuffer[i] = 0;
	}
	startIndex = 0;
	size = 0;
	
	//adc timer
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()/UPDATE_RATE); 	//interrupt rate is 20hz
	TimerEnable(TIMER0_BASE, TIMER_A);
	IntPrioritySet(INT_TIMER0A, 1);
	TimerControlTrigger(TIMER0_BASE, TIMER_A, 1);
	
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	IntEnable(INT_TIMER0A);
	IntMasterEnable();
	EnableInterrupts();
}
