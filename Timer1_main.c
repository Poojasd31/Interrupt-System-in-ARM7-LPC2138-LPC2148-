#include<lpc21xx.h>
#include "PLL.h"
#define LED 17

void timer1_isr(void) __irq
{
	IOPIN0 ^= (1<<LED);
	T1IR = 1;
	VICVectAddr = 0x0;
}


void main()
{
	PINSEL1 = 0X00000000; //AS  a GPIO
	IODIR0 |= (1<<LED); //LED as an Output
	
	//PLL initializations
	PLL_SET();
	
	T1PR = 29999;  //Presacle
	T1MCR =0X0018; //reset and matching
	T1MR1 = 1000; //match value=1ms
	T1TCR = 0X01; //ENABLE TIMER
	
	VICIntEnable |= (1 << 5);     // Enable Timer1 interrupt
  VICVectAddr4 = (unsigned long)timer1_isr;  // ISR address
  VICVectCntl4 = (1 << 5) | 5;               // Enable slot and assign Timer0
	
	while(1)
	{
		
	}
}