/*
 * GLcd.c
 *
 *  Created on: Mar 11, 2024
 *      Author: Ahmed Sayed
 */
#include "Glcd.h"
#include <stdLib.h>
#include "Gpio.h"
#include "glcd-font.h"
#include <util/delay.h>
uint8 X_Address_Increment = X_FIRST_ADDRESS;
uint8 j =0;
/*  ********************************************************************************************
 *   Function Name : GLCD_Get_Command(constant uint8 command)
 *   Description   : This Function Used To Send Commands To Graphical LCD
 *   Parameters    :  Command This constant Variable used to Carry The Command Data For LCD
 *   Return Value  : Void
 *   Remarks       : None
 * *********************************************************************************************/
void GLCD_Get_Command(const uint8 command)
{
	GPIO_writePin(PORT_COMMAND_BUS,RS_PIN,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(PORT_COMMAND_BUS,EN_PIN,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePort(PORT_DATA_BUS,command);
	_delay_ms(1);
	GPIO_writePin(PORT_COMMAND_BUS,EN_PIN,LOGIC_LOW);
	_delay_ms(1);
}
/*  ********************************************************************************************
 *   Function Name : GLCD_Write_Data(const uint8 data)
 *   Description   : This Function Used To Receive Data That Needed To Appear on  Graphical LCD
 *   Parameters    :  Data This constant Variable used to Carry The Data that Needed To appear on LCD
 *   Return Value  : Void
 *   Remarks       : None
 * *********************************************************************************************/
void GLCD_Write_Data(const uint8 data)
{
	GPIO_writePin(PORT_COMMAND_BUS,RS_PIN,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(PORT_COMMAND_BUS,EN_PIN,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePort(PORT_DATA_BUS,data);
	_delay_ms(1);
	GPIO_writePin(PORT_COMMAND_BUS,EN_PIN,LOGIC_LOW);
	_delay_ms(1);


}
/*  ********************************************************************************************
 *   Function Name : GLCD_Init()
 *   Description   : This Function Used To Initialize The Graphical LCD
 *   Parameters    : void
 *   Return Value  : Void
 *   Remarks       : None
 * *********************************************************************************************/
void GLCD_Init()
{
    GPIO_setupPortDirection(PORT_DATA_BUS,PORT_OUTPUT);
    GPIO_setupPortDirection(PORT_COMMAND_BUS,PORT_OUTPUT);
    GLCD_PageSelect(Left_Page);
    GPIO_writePin(PORT_COMMAND_BUS,RESET_PIN,LOGIC_HIGH);
    _delay_ms(20);
    GLCD_Get_Command(DISPLAY_OFF);
    GLCD_Get_Command(Y_FIRST_ADDRESS);
    GLCD_Get_Command(X_FIRST_ADDRESS);
    GLCD_Get_Command(Z_FIRST_ADDRESS);
    GLCD_Get_Command(DISPLAY_ON);
}
/*  ********************************************************************************************
 *   Function Name : GLCD_Clear_Display()
 *   Description   : This Function Used To Clear The Data From LCD
 *   Parameters    : void
 *   Return Value  : Void
 *   Remarks       : None
 * *********************************************************************************************/
void GLCD_Clear_Display()
{
	uint8 i=0;
	uint8 j=0;
	GPIO_writePin(PORT_COMMAND_BUS,LEFT_SEGMENT_PIN,LOGIC_LOW);
	GPIO_writePin(PORT_COMMAND_BUS,RIGHT_SEGMENT_PIN,LOGIC_LOW);
	for (i=0;i<8;i++)
	{
		GLCD_Get_Command((X_FIRST_ADDRESS)+i);
		for (j=0;j<64;j++)
		{
			GLCD_Write_Data(clear_lcd);
		}

	}

	GLCD_Get_Command(Y_FIRST_ADDRESS);
	GLCD_Get_Command(X_FIRST_ADDRESS);

}
/*  ********************************************************************************************
 *   Function Name : Set_Cursor(uint8 x, uint8 y)
 *   Description   : This Function Used To Set a Cursor In a Specific Position
 *   Parameters    : x , y variables Are Used To Set The Location in LCD
 *   Return Value  : Void
 *   Remarks       : Follow The DataSheet Registers
 * *********************************************************************************************/
void Set_Cursor(uint8 x, uint8 y)
{

	GLCD_Get_Command((X_FIRST_ADDRESS&0xF8) | (x & 0x07));
	_delay_ms(1);
    GLCD_Get_Command((Y_FIRST_ADDRESS&0xC0) | (y & 0x3E));

}
/*  ********************************************************************************************
 *   Function Name : glcd_writeChar(char * chr,Page_Num_Select page)
 *   Description   : This Function Used To Write a Charchter On Graphical LCD
 *   Parameters    : Pointer To Char , Page Two Parameters First One To Carry The Array That Draw The Char On lCD
 *   Page Select To Select The Page On LCD
 *   Return Value  : Void
 *   Remarks       : The Charcheters In The Graphical LCD Is Drawn According To An Array Because
 *                   All Charchters Drawn In LCD Are 5*7 Font Not 8*8 As Normal LCD
 * *********************************************************************************************/
void glcd_writeChar(char * chr,Page_Num_Select page)
{
	uint8 i=0;
	GLCD_PageSelect(page);
	for(i=0;i<5;i++)
	{
		GLCD_Write_Data(*(chr+i));
	}
}
/*  ********************************************************************************************
 *   Function Name : glcd_writeStr( char (*ptr)[5])
 *   Description   : This Function Used To Write a String But With 2D Array To Draw Charchtes And Loop
 *   On This Array To Display All Charachters Next To Each Other
 *   Parameters    : Pointer To Array Each Array Consist of Number ( N ) : N here is The Number of Element Per Each Array
 *   Return Value  : Void
 *   Remarks       : None
 * *********************************************************************************************/
void glcd_writeStr( char (*ptr)[5])
{
	uint8 i ,j;
	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			GLCD_Write_Data(*(ptr[i]+j));
		}
	}
}
/*********************************************************************************************
 *   Function Name : GLCD_PageSelect(Page_Num_Select page)
 *   Description   : This Function Used Select The Page of Two Pages In LCD
 *   Parameters    : Page Is Variable From User Defined Data Type Enum To Select Page
 *   Return Value  : Void
 *   Remarks       : None
 **********************************************************************************************/
void GLCD_PageSelect(Page_Num_Select page)
{
	switch (page)
	{
	case Left_Page:
		GPIO_writePin(PORT_COMMAND_BUS,LEFT_SEGMENT_PIN,LOGIC_LOW);
		GPIO_writePin(PORT_COMMAND_BUS,RIGHT_SEGMENT_PIN,LOGIC_HIGH);
		break;
	case Right_Page:
		GPIO_writePin(PORT_COMMAND_BUS,LEFT_SEGMENT_PIN,LOGIC_HIGH);
		GPIO_writePin(PORT_COMMAND_BUS,RIGHT_SEGMENT_PIN,LOGIC_LOW);
		break;
	case both_pages:
		GPIO_writePin(PORT_COMMAND_BUS,LEFT_SEGMENT_PIN,LOGIC_LOW);
		GPIO_writePin(PORT_COMMAND_BUS,RIGHT_SEGMENT_PIN,LOGIC_LOW);
		break;

	default :
		GPIO_writePin(PORT_COMMAND_BUS,LEFT_SEGMENT_PIN,LOGIC_LOW);
		GPIO_writePin(PORT_COMMAND_BUS,RIGHT_SEGMENT_PIN,LOGIC_HIGH);
	}
}
/*********************************************************************************************
 *   Function Name : GLCD_wString(uint8 *str,Page_Num_Select page)
 *   Description   : This Function Used To Write a String But Not With Draw Charcheters just Write a String
 *   Parameters    : (*str , page) is Two Variables To Select Page and also Str is variable
 *   Return Value  : Void
 *   Remarks       : This Function As Following :
 *   It Takes The String and then makes some operations :
 *   -) While This String != Null
 *   -) Also As The The Charachters That Displayed On LCD Are 5*7 That Means Each Char Mapped
 *    Intro 5 bytes each byte contain 7 bits
 *    As The Array contain each 5-bytes for every character
 *
 *    So StartFont ( * str - 32 ) *5
 *    each  byte - 32 As 32 Is The First Ascii Code in The Mapped Array
 *    *5 is just for bitmap of each byte
 *
 *    will make this for each byte in the string ,,, also then end font = start + 5
 *
 *    this condition to loop on the 5 bytes from initial byte till fifth byte
 *
 *    will increment * str till Null And exit the loop
 *
 **********************************************************************************************/
void GLCD_wString(uint8 *str,Page_Num_Select page)
{
	uint16 i=0;
	GLCD_PageSelect(page);
	uint16 startfont=0,endfont=0;
	while (*str)
	{
		startfont=(*str-32)*5;
		endfont=startfont + 5;
		for (i=startfont;i<endfont;i++)
		{
			GLCD_Write_Data(sys5x7[i]);
			_delay_ms(10);
		}
		str++;
	}
}
/*********************************************************************************************
 *   Function Name : GLCD_displayImage(const unsigned char *str,uint8 x)
 *   Description   : This Function Used To Display Image On Graphical LCD
 *   Parameters    : Variable of str is the array from 1024 ,, X is For Shift The Img on LCD
 *   Return Value  : Void
 *   Remarks       : This Function is Working as following
 *   While i < 1024
 *   check on number of columns if it reached 64 As The Page Have Columns from 0 to 64
 *                                                  The Second Page Have Columns from 65 to 128
 *   if J The Variable That Responsible to Increment The Coulums if The First 64 byte that means
 *   That First Page Finished and need to accessed The Second page
 *   when j reach 128 it will accessed again the left page with increment into the next page and so on
 **********************************************************************************************/
void GLCD_displayImage(const unsigned char *str,uint8 x )
{
	uint16 i = 0;
	uint16 X_Address = (X_FIRST_ADDRESS&0xF8) | (x & 0x07);
	while(i < 1024)
	{
		if (j == 64 ) {
			GLCD_PageSelect(Right_Page);
			GLCD_Get_Command(X_Address);
		} else if (j == 128){
			X_Address++;
			GLCD_PageSelect(Left_Page);
			GLCD_Get_Command(X_Address);
			j = 0;
		}
		GLCD_Write_Data(str[i]);
		i++;
		j++;
	}
}
/*********************************************************************************************
 *   Function Name : GLCD_diplayGIF(const unsigned char **images, uint8 NO_Images)
 *   Description   : This Function Used To Display a GIF On Graphical LCD
 *   Parameters    : A 2D Array Used To Holds a An Images Each Array Contains 1024
 *   Return Value  : Void
 *   Remarks       : None
 **********************************************************************************************/
void GLCD_diplayGIF(const unsigned char **images, uint8 NO_Images)
{
	uint8 i;
	for(i = 0; i < NO_Images; i++){
		GLCD_displayImage(images[i],0);

	}
}
/*********************************************************************************************
 *   Function Name : LCD_IntgerToString(uint32 data,Page_Num_Select page)
 *   Description   : This Function Used To a numbers as a strings on LCD
 *   Parameters    : The Data , page variables
 *   Data used : The Number Nedded To Display we convert This Number into Ascii And Save In Array
 *   And Then Convert Each ASCII IN The Array Into String Through ITOA Function
 *   Return Value  : Void
 *   Remarks       : None
 **********************************************************************************************/
void LCD_IntgerToString(uint32 data,Page_Num_Select page)
{
	char buff[16];
	itoa(data,buff,10);
	GLCD_wString(buff,page);
}
