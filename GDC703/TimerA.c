/*
 * TimerA.c
 *
 *  Created on: Jan 14, 2018
 *      Author: leo.liu
 */
#include <msp430.h>
#include "TimerA.h"
//1fenzhong
volatile unsigned char interrupt_count = 0;
void TimerA_Init(void)
{
	  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	  //P5DIR |= BIT1;                            // P5.1 output
	  CCTL0 = CCIE;                             // CCR0 interrupt enabled
	  CCR0 = 50000;
	  TACTL = TASSEL_2 + MC_1;                  // SMCLK, up mode
	  //__bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMERA0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
 // P5OUT ^= BIT1;                            // Toggle P5.1
  CCR0 += 50000;                            // Add Offset to CCR0
  interrupt_count++;
}
