#include<lpc21xx.h>
#include "LCD.h"
#include "PLL.h"

unsigned int ADC;
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

void AD0ISR(void)__irq
{

     ADC=(AD0DR2&0x0000FFC0);
     ADC=ADC>>6;
	 
     VICVectAddr = 0x00;  // The isr has finished
}
int main()
{
 PLL_SET();
 LCD_Initialize();;
 LCD_CMD(0x80);
 LCD_String("ADC_ISR");

 VICIntEnable |= (1<<18);   //en ext int0
 VICVectCntl0 = (1<<5)|18;     //selected slot 0 and enable it(1<<5) and put valu of ext.int0(14)
 VICVectAddr0 = (unsigned) AD0ISR;  //give  isr name to addr0 reg

  PINSEL1 = 0x04000000;
  AD0INTEN= (1<<2);
  AD0CR   = 0x00210E04;

//AD0CR   = 0x00210E04;

   while(1)
   {
    LCD_CMD(0xC0);
    LCD_Data((ADC/1000)+'0');
    LCD_Data(((ADC/100)%10)+'0');
    LCD_Data(((ADC/10)%10)+'0');
    LCD_Data((ADC%10)+'0');
   }

}
