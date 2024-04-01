/*
 * GLcd.h
 *
 *  Created on: Mar 11, 2024
 *      Author: Ahmed Sayed
 */

#ifndef GLCD_H_
#define GLCD_H_
#include "std_types.h"
/**********************************************************************************************
 *                         PORTS For Commands and Data bus Definitions                         +
 **********************************************************************************************/

#define PORT_DATA_BUS PORTA_ID
#define PORT_COMMAND_BUS PORTC_ID

/* ********************************************************************************************
 *                  Enum : Used To Choose The Page Needed For use on The LCD                    *
 * *********************************************************************************************/
typedef enum
{
	Left_Page,Right_Page,both_pages

}Page_Num_Select;

/* *******************************************************************************************
 *                        Pins Used For { RS , EN , CS1 , CS2 , RESET }                       *
 **********************************************************************************************/
#define RS_PIN  PIN2_ID
#define EN_PIN  PIN3_ID
#define LEFT_SEGMENT_PIN PIN0_ID
#define RIGHT_SEGMENT_PIN PIN1_ID
#define RESET_PIN PIN4_ID
/* ******************************************************************************************
 *                   Prototypes Used For  Functions of  Graphical LCD                       *
 * ****************************************************************************************** */
void GLCD_Get_Command( const uint8 command);
void GLCD_Write_Data(const  uint8 data);
void GLCD_Init();
void GLCD_Clear_Display();
void Set_Cursor(uint8 x, uint8 y);
void glcd_writeChar( char * chr,Page_Num_Select page);
void glcd_writeStr( char (*ptr)[5]);
void GLCD_PageSelect(Page_Num_Select page);
void GLCD_wString(uint8 *str,Page_Num_Select page);
void GLCD_displayImage(const unsigned char *str,uint8 x );
void GLCD_diplayGIF(const unsigned char **images, uint8 NO_Images);
void LCD_IntgerToString(uint32 data,Page_Num_Select page);
/* ******************************************************************************************
 *                                   GLCD Common Addresses                                   *
 *********************************************************************************************/
#define DISPLAY_OFF       0X3E
#define Y_FIRST_ADDRESS   0X40
#define X_FIRST_ADDRESS   0xB8
#define Z_FIRST_ADDRESS   0xC0
#define DISPLAY_ON        0X3F
#define clear_lcd         0x00

#endif /* GLCD_H_ */
