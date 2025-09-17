#include<LPC21XX.h>

//Control Pins for LCD
#define RS 17
#define RW 18
#define EN 19
//Data Pins for LCD
#define D4 20
#define D5 21
#define D6 22
#define D7 23

//Forward Declaration
void LCD_Initialize();
void LCD_CMD(unsigned char );
void LCD_Data(unsigned char);
void LCD_Bit(unsigned char);
void LCD_String(char *str);