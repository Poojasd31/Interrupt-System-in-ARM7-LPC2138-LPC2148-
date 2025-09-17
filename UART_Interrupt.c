#include <LPC21XX.h>
#include "PLL.h"

#define led1 17
#define sw1  14
#define sw2  15

void UARTISR(void)__irq;
void initInterrupt(void);
void delay(int);          
char read1;


void main()
{
	char Read_result;
	PINSEL0|=0x00000000;
	PINSEL1|=0x00000000;
	PINSEL2|=0x00000000;
	IODIR0|=(1<<led1);
  IODIR0|=(0<<sw1);	
	IODIR0|=(0<<sw2);	
	PLL_SET();
	UART0_Init()
	initInterrupt();
    while(1)                
    {
			   
				if(read1=='A')
				{
					  delay(30);
						IOPIN0 ^=(1<<led1);  				
					  
				}	
				if(read1=='B')
				{
					  delay(30);
						IOCLR0=(1<<led1);  				
					  
				}
		}
}

//Initialization function of UART
void UART0_Init()
{
	U0LCR = 0X83; //(DLAB=1 , WORD LENGTH=8 BIt)
	U0DLM = 0X00; //For 9600 Baud rate
	U0DLL = 0XC3; 
	U0LCR = 0X03; //Disable DLAB
	//To enable Uart interrupt
	//U0IER = 0X00000001; // It enables receive Data available interrupt
	
}

////ISR Code for UART
//void UART_ISR(void) __irq
//{
//	
//		rx_data = U0RBR ;  //store it into ex_data from receive buffer register

//	  VICVectAddr = 0X00; //THE ISR has finished
//}


void initInterrupt(void)
{
 VICIntEnable=(1<<6);
 VICVectCntl0=(1<<5)|6;
 VICVectAddr0=(unsigned) UARTISR;
  U0IER=(1<<0);
}

void UARTISR(void)__irq
{
  read1=U0RBR;
  VICVectAddr=0x00;
}



void delay(int t)
{
	int i,j;
	for(i=0;i,t;i++)
	{
		for(j=0;j<60000;j++)
		{
		}
	}
}