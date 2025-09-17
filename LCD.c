#include "LCD.h"

void LCD_Initialize()
{
	PINSEL2 = 0X00000000;
	//To set a pin as a Output
	IODIR1 |= (1<<RS) | (1<<RW) | (1<<EN) | (1<<D4) | (1<<D5) | (1<<D6) | (1<<D7);
	delay(50);
	LCD_CMD(0x02); /* Initialize lcd in 4-bit mode */
  LCD_CMD(0x28); /* 2 lines */ 
  LCD_CMD(0x0C); /* Display on cursor off */ 
  LCD_CMD(0x06); /* Auto increment cursor */ 
  LCD_CMD(0x01); /* Display clear */ 
  LCD_CMD(0x80); /* First line first position */
}

void LCD_CMD(unsigned char CMD)
{
	IOCLR1 = (1<<RS) | (1<<RW); //RS=0 Cmd reg and RW = 0 Write Operation
	
	//UPPER Nibble
	LCD_Bit(CMD >> 4);
	IOSET1 = (1<<EN);
	delay(5);
	IOCLR1 = (1<<EN);
	 
	//Lower Nibble
	LCD_Bit(CMD & 0X0F);
	IOSET1 = (1<<EN);
	delay(5);
	IOCLR1 = (1<<EN);
}

void LCD_Data(unsigned char Data)
{
	IOSET1 = (1<<RS);  //RS=1 Data reg
	IOCLR1 = (1<<RW); //RW = 0 Write Operation
	
	//UPPER Nibble
	LCD_Bit(Data >> 4);
	IOSET1 = (1<<EN);
	delay(5);
	IOCLR1 = (1<<EN);
	 
	//Lower Nibble
	LCD_Bit(Data & 0X0F);
	IOSET1 = (1<<EN);
	delay(5);
	IOCLR1 = (1<<EN);
}

void LCD_Bit(unsigned char Bit)
{
	//For D4
	if(Bit & 0x01)
		IOSET1 = (1<<20);
	else
		IOCLR1 = (1<<20);
	
	//For D5
	if(Bit & 0x02)
		IOSET1 = (1<<21);
	else
		IOCLR1 = (1<<21);
	
	//For D6
	if(Bit & 0x04)
		IOSET1 = (1<<22);
	else
		IOCLR1 = (1<<22);
	
	//For D7
	if(Bit & 0x08)
		IOSET1 = (1<<23);
	else
		IOCLR1 = (1<<23);	
}

void LCD_String(char *str)
{
	while(*str)
	LCD_Data(*str ++);

}
	