#include<LPC21XX.h>

#define LED 17

void timer0_isr(void) __irq ;

void main()
{
	PINSEL1 = 0X00000000; //AS  a GPIO
	IODIR0 |= (1<<LED); //LED as an Output
	
	//PLL initializations
	PLL_SET();
	
	//For Timers
	T0PR = 29999;
	T0MR0 = 1000 ;         // Match value = 1000 
  T0MCR = 0x0003;           // for match value and Reset on MR0
  T0TCR =0X01;   //Enable Timer
	
	VICIntEnable |= (1 << 4);     // Enable Timer0 interrupt
  VICVectAddr4 = (unsigned long)timer0_isr;  // ISR address
  VICVectCntl4 = (1 << 5) | 4;               // Enable slot and assign Timer0
	
	while(1)
	{
	}
}



// Timer0 ISR
void timer0_isr(void) __irq 
	{
    IO0PIN ^= (1<<LED);  // Toggle LED
    T0IR = 1;       // Interrupt flag for match channel 0
    VICVectAddr = 0x0; // isr has finished
}
