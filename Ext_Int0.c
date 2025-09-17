#include <LPC21Xx.h>

#define LED 17 

void myisr(void) __irq;

int main() {
   
    PINSEL1 = 0x00000001; 
    IODIR0 = (1<<LED); 

    // Interrupt setup -ext
	  EXTMODE = 0X01;
	  EXTPOLAR  = 0X00;
    
    VICIntEnable |= (1 << 14);     // Enable  interrupt
    VICVectCntl0 = (1 << 5) | 14;               // Enable slot 
	  VICVectAddr0 = (unsigned)myisr;  // ISR address

    while (1) {
     
    }

    return 0;
}

//  ISR
void myisr(void) __irq {
    IO0PIN ^= (1<<LED);  // Toggle LED
    EXTINT = 0X01;       // Clear interrupt flag
    VICVectAddr = 0; // Acknowledge Interrupt
}
