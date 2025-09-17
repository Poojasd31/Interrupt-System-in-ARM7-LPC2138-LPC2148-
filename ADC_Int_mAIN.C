#include<lpc21xx.h>
#include "LCD.h"
#include "PLL.h"
//ADC Channel 2 -P0.29

unsigned int adc_read = 0;
void ADC_ISR(void) __irq;
void delay(int);


void main()
{

	PINSEL1 = 0X04000000; //P0.29 as an ADC pin
	IODIR0 &= ~(1<<29);  //ADC AS an Input
	
	PLL_SET(); //Set up PLL
	LCD_Initialize(); //Initialize LCD
	LCD_CMD(0x80); //1st Row of LCD
	LCD_String("ADC Interrupt"); //Print on 1st line
	
	//ADC Conf
	AD0CR |= (1<<2) | (7<<8) | (1<<16) | (1<<21);  //Channel 2 , Burst Mode = 1(Conversion start from 000) ,7 for PCLK/7=> 30MHz/7= 4.2Mhz ,21=1 for Operational mode
	AD0INTEN = (1<<2);
	
	VICIntEnable |= (1<<18); //Enable AD0 Interrupt
	VICVectCntl0 = (1<<5) | 18; //Enable slot
	VICVectAddr0 = (unsigned) ADC_ISR; //Assign address
	
	
	while(1)
	{
	  
	
		LCD_CMD(0xC0);
		LCD_String("Values:");
	  LCD_Data((adc_read/1000)+'0'); //D4 
    LCD_Data(((adc_read/100)%10)+'0');//d3
    LCD_Data(((adc_read/10)%10)+'0');//D2
    LCD_Data((adc_read%10)+'0');//D1
	}
}


// ADC interrupt 
void ADC_ISR(void) __irq
{
  adc_read = ((AD0GDR & 0X0000FFC0) >> 6); //Read the value
	
  VICVectAddr = 0; // ISR is finished
}


void delay(int t)
{
	int i,j;
	for(i=0;i<t;i++)
	{
		for(j=0;j<60000;j++)
		{
		}
	}
}
