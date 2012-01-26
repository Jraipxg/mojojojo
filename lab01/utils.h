/*
	File Name: utils.h
	Authors: Joshua James and Mohit Taneja
	Initial Creation Date: 9/12/11
	Description: General useful functions
	Lab Number: 3
	TA: Sundeep
	Date of last revision: 9/19/11
	Hardware configuration: 
*/

#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

//#define TRUE 	1
//#define FALSE 	0

#define GPIO_PORTG_DATA_R       (*((volatile unsigned long *)0x400263FC))
#define GPIO_PORTG_DIR_R        (*((volatile unsigned long *)0x40026400))
#define GPIO_PORTG_DEN_R        (*((volatile unsigned long *)0x4002651C))
#define GPIO_PORTG2             (*((volatile unsigned long *)0x40026010))
#define SYSCTL_RCGC1_R          (*((volatile unsigned long *)0x400FE104))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC1_TIMER0     0x00010000  // timer 0 Clock Gating Control
#define SYSCTL_RCGC2_GPIOG      0x00000040  // Port G Clock Gating Control
#define SYSCTL_RCGC2_GPIOF      0x00000020  // Port F Clock Gating Control


typedef struct Tuple
{
	int32_t first;
	int32_t second;
} Tuple;

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
__asm void Delay(unsigned long ulCount);

extern uint32_t iabs(int32_t value);
#endif
