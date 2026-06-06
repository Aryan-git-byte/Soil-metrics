/*
 * ILI9341_16bit.h
 *
 *  Created on: Apr 29, 2024
 *      Author: LPT-23-058
 */

#ifndef INC_ILI9341_16BIT_H_
#define INC_ILI9341_16BIT_H_

#include "fonts_h.h"

#define ILI9341_WIDTH       320
#define ILI9341_HEIGHT      480

// ILI9341 command definitions
#define ILI9341_CMD_SOFTWARE_RESET         0x01
#define ILI9341_CMD_POWER_CONTROL_1        0xC0
#define ILI9341_CMD_POWER_CONTROL_2        0xC1
#define ILI9341_CMD_VCOM_CONTROL_1         0xC5
#define ILI9341_CMD_VCOM_CONTROL_2         0xC7
#define ILI9341_CMD_MEMORY_ACCESS_CTRL     0x36
#define ILI9341_CMD_COL_ADDR_SET           0x2A
#define ILI9341_CMD_PAGE_ADDR_SET          0x2B
#define ILI9341_CMD_PIXEL_FORMAT_SET       0x3A
#define ILI9341_CMD_DISPLAY_FUNCTION_CTRL  0xB6
#define ILI9341_CMD_ENTRY_MODE_SET         0x11
#define ILI9341_CMD_DISPLAY_ON             0x29

void ILI9341_Initial(void);
void Write_Cmd_Data(uint16_t cmd_data);
void Write_Cmd(uint16_t cmd);
void Write_Data(uint16_t data);
void  Write_Data_U16(uint16_t y);
void LCD_SetPos(uint16_t x0,uint16_t x1,uint16_t y0,uint16_t y1);
void setRotation(uint8_t rotate);
void ClearScreen(uint16_t bColor);

void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color); //Draw single pixel to ILI9341

void LCD_Rect(unsigned int x0,unsigned int y0, unsigned int w,unsigned int h, uint16_t color);
void LCD_Fill_Rect(unsigned int x0, unsigned int y0, unsigned int w, unsigned int h, uint16_t color);
// Circle drawing functions
void LCD_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void LCD_drawUpperHalfCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void LCD_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
void LCD_fillArc(uint16_t x, uint16_t y, uint16_t radius, uint16_t startAngle, uint16_t endAngle, uint16_t color);
void LCD_drawGaugePointer(uint16_t x, uint16_t y, uint16_t radius, float angle, uint16_t color);
// Line drawing functions
void LCD_drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
void LCD_drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
void LCD_drawDiagonalLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void LCD_drawFilledTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_drawChar(unsigned int x,unsigned int y,unsigned char value,unsigned int dcolor,unsigned int bgcolor);
void LCD_WriteString(uint16_t x, uint16_t y,  uint8_t* str, uint16_t strlength, FontDef font, uint16_t color, uint16_t bgcolor);
void drawPointer(int x0, int y0, int radius, int value, uint16_t color);
void LCD_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data);

uint8_t ILI9341_getRotation(void);
#endif /* INC_ILI9341_16BIT_H_ */
