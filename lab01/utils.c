/*
	File Name: utils.c
	Authors: Joshua James and Mohit Taneja
	Initial Creation Date: 9/12/11
	Description: General useful functions
	Lab Number: 3
	TA: Sundeep
	Date of last revision: 9/19/11
	Hardware configuration: 
*/

#include "utils.h"

uint32_t iabs(int32_t value)
{
	if(value < 0)
	{
		return value * -1;
	}
	return value;
}

// delay function for testing from sysctl.c
// which delays 3*ulCount cycles
__asm void
Delay(unsigned long ulCount)
{
    subs    r0, #1
    bne     Delay
    bx      lr
}

