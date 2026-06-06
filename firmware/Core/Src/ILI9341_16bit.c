#include "main.h"
#include "ILI9341_16bit.h"
#include "fonts_h.h"
#include <stdlib.h>

static uint8_t rotationNum=1;
//===============================================================



//===============================================================
//WRITE COMMAND PARAMETER

void  Write_Cmd_Data (uint16_t cmd_data)
{
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET); // RS=1;
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET); //CS=0;
	HAL_GPIO_WritePin(RD_GPIO_Port, RD_Pin, GPIO_PIN_SET); //RD=1;
	GPIOD -> ODR = cmd_data;
	HAL_GPIO_WritePin(WR_GPIO_Port, WR_Pin, GPIO_PIN_RESET); //WR=0;
//	HAL_Delay(5);
	HAL_GPIO_WritePin(WR_GPIO_Port, WR_Pin, GPIO_PIN_SET);  //_WR=1;
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET); //CS=1;

}

//==============================================================
//WRITE DATA WORD


//=============================================================
//WRITE COMMAND

void Write_Cmd(uint16_t cmd)
{
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin,GPIO_PIN_RESET); // RS=0;
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET); //CS=0;
	HAL_GPIO_WritePin(RD_GPIO_Port, RD_Pin, GPIO_PIN_SET); //RD=1;
	GPIOD -> ODR = cmd;
	HAL_GPIO_WritePin(WR_GPIO_Port, WR_Pin, GPIO_PIN_RESET); //WR=0;
//	HAL_Delay(5);
	HAL_GPIO_WritePin(WR_GPIO_Port, WR_Pin, GPIO_PIN_SET);  //_WR=1;
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET); //CS=1;
}

//===================================================================
//WRITE DATA CHAR

void Write_Data(uint16_t data)
{
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET); // RS=1;
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET); //CS=0;
	HAL_GPIO_WritePin(RD_GPIO_Port, RD_Pin, GPIO_PIN_SET); //RD=1;
	GPIOD -> ODR = data;
	HAL_GPIO_WritePin(WR_GPIO_Port, WR_Pin, GPIO_PIN_RESET); //WR=0;
//	HAL_Delay(5);
	HAL_GPIO_WritePin(WR_GPIO_Port, WR_Pin, GPIO_PIN_SET);  //_WR=1;
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET); //CS=1;
}


//=============================================================
//lcd initial

void ILI9341_Initial(void)

{
	HAL_Delay(5);
	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET); //RES=0;
	HAL_Delay(10);
	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET); //RES=1;
	HAL_Delay(120);

 	Write_Cmd(0x28);    //Display OFF

 	// Configure power control settings
 	Write_Cmd(ILI9341_CMD_POWER_CONTROL_1);
 	Write_Cmd_Data(0x22); // VRH = 4.60
// 	Write_Cmd_Data(0x10); // SAP = 0x10

 	   Write_Cmd(ILI9341_CMD_POWER_CONTROL_2);
 	  Write_Cmd_Data(0x11); // VC = 0x10

 	    // Configure VCOM control
 	   Write_Cmd(ILI9341_CMD_VCOM_CONTROL_1);
 	  Write_Cmd_Data(0x3E); // VCM = 0x3E
 	   Write_Cmd_Data(0x28); // VDV = 0x28

 	   Write_Cmd(ILI9341_CMD_VCOM_CONTROL_2);
 	  Write_Cmd_Data(0xA9); // VCM = 0x86

 	    // Set memory access control (adjust as needed)
 	   Write_Cmd(ILI9341_CMD_MEMORY_ACCESS_CTRL);
 	  Write_Cmd_Data(0x08); // MY = 1, MX = 0, MV = 1, ML = 0, RGB = 0

 	    // Set column address range
 	   Write_Cmd(ILI9341_CMD_COL_ADDR_SET);
 	  Write_Cmd_Data(0x0000); // Start column
 	   Write_Cmd_Data(0x01DF); // End column

 	    // Set page address range
 	   Write_Cmd(ILI9341_CMD_PAGE_ADDR_SET);
 	  Write_Cmd_Data(0x0000); // Start page
 	 Write_Cmd_Data(0x013F); // End page

 	    // Set pixel format (16 bits per pixel)
 	   Write_Cmd(ILI9341_CMD_PIXEL_FORMAT_SET);
 	  Write_Cmd_Data(0x55); // 16 bits per pixel (RGB565)

 	    // Configure display function control
 	   Write_Cmd(ILI9341_CMD_DISPLAY_FUNCTION_CTRL);
 	  Write_Cmd_Data(0x0A); // Scan direction
// 	  Write_Cmd_Data(0x02); // Scan direction
// 	 Write_Cmd_Data(0x02); // Scan direction

	Write_Cmd(0x34);

	Write_Cmd(0xB7);
	Write_Cmd_Data(0x0007);

 	Write_Cmd(0xB6);    // Display Function Control
 	 Write_Cmd_Data(0x02);
 	 Write_Cmd_Data(0x02);
//	Write_Cmd_Data(0x000A);
//	Write_Cmd_Data(0x0082);
//	Write_Cmd_Data(0x0027);
//	Write_Cmd_Data(0x0000);

	Write_Cmd(0xF6);    // Interface Control
	Write_Cmd_Data(0x0001);
	Write_Cmd_Data(0x001D);

	Write_Cmd(0xF2);    // 3Gamma Function Disable
	Write_Cmd_Data(0x0000);

	Write_Cmd(0x26);    // Gamma Curve Select
	Write_Cmd_Data(0x0001);

	Write_Cmd(0xE0);    //  Positive Gamma Correction
//	Write_Cmd_Data(0x000F);
//	Write_Cmd_Data(0x003F);
//	Write_Cmd_Data(0x002F);
//	Write_Cmd_Data(0x000C);
//	Write_Cmd_Data(0x0010);
//	Write_Cmd_Data(0x000A);
//	Write_Cmd_Data(0x0053);
//	Write_Cmd_Data(0x00D5);
//	Write_Cmd_Data(0x0040);
//	Write_Cmd_Data(0x000A);
//	Write_Cmd_Data(0x0013);
//	Write_Cmd_Data(0x0003);
//	Write_Cmd_Data(0x0008);
//	Write_Cmd_Data(0x0003);
//	Write_Cmd_Data(0x0000);
	Write_Cmd_Data(0x000F);
	Write_Cmd_Data(0x001A);
	Write_Cmd_Data(0x000F);
	Write_Cmd_Data(0x0018);
	Write_Cmd_Data(0x002F);
	Write_Cmd_Data(0x0028);
	Write_Cmd_Data(0x0020);
	Write_Cmd_Data(0x0022);
	Write_Cmd_Data(0x001F);
	Write_Cmd_Data(0x001B);
	Write_Cmd_Data(0x0023);
	Write_Cmd_Data(0x0037);
	Write_Cmd_Data(0x0000);
	Write_Cmd_Data(0x0007);
	Write_Cmd_Data(0x0002);
	Write_Cmd_Data(0x0010);

	Write_Cmd(0xE1);    //  Negative Gamma Correction
//	Write_Cmd_Data(0x0000);
//	Write_Cmd_Data(0x0000);
//	Write_Cmd_Data(0x0010);
//	Write_Cmd_Data(0x0003);
//	Write_Cmd_Data(0x000F);
//	Write_Cmd_Data(0x0005);
//	Write_Cmd_Data(0x002C);
//	Write_Cmd_Data(0x00A2);
//	Write_Cmd_Data(0x003F);
//	Write_Cmd_Data(0x0005);
//	Write_Cmd_Data(0x000E);
//	Write_Cmd_Data(0x000C);
//	Write_Cmd_Data(0x0037);
//	Write_Cmd_Data(0x003C);
//	Write_Cmd_Data(0x000F);
	Write_Cmd_Data(0x000F);
	Write_Cmd_Data(0x001B);
	Write_Cmd_Data(0x000F);
	Write_Cmd_Data(0x0017);
	Write_Cmd_Data(0x0033);
	Write_Cmd_Data(0x002C);
	Write_Cmd_Data(0x0029);
	Write_Cmd_Data(0x002E);
	Write_Cmd_Data(0x0030);
	Write_Cmd_Data(0x0030);
	Write_Cmd_Data(0x0039);
	Write_Cmd_Data(0x003F);
	Write_Cmd_Data(0x0000);
	Write_Cmd_Data(0x0007);
	Write_Cmd_Data(0x0003);
	Write_Cmd_Data(0x0010);

	Write_Cmd(0x20);    //Display inversino on

 	Write_Cmd(0x11);    //Exit Sleep
	HAL_Delay(120);
 	Write_Cmd(0x29);    //Display on
	HAL_Delay(50);
	Write_Cmd(0x2C);
	HAL_Delay(50);



}

void Enter_Sleep(void)
{
	Write_Cmd(0x28);     // Display off
	Write_Cmd(0x10);     // Enter Sleep mode
}

void Exit_Sleep(void)
{
	Write_Cmd(0x11);     // Sleep out
	HAL_Delay(120);
	Write_Cmd(0x29);     // Display on
}

//===============================================================
//Define the coordinate
void LCD_SetPos(uint16_t x0,uint16_t x1,uint16_t y0,uint16_t y1)
{
 	Write_Cmd(0x2A);
 	Write_Cmd_Data(x0 >> 8);
	Write_Cmd_Data (x0 & 0xff);
	Write_Cmd_Data(x1 >> 8);
	Write_Cmd_Data (x1 & 0xff);
	Write_Cmd(0x2B);
	Write_Cmd_Data(y0 >> 8);
	Write_Cmd_Data (y0 & 0xff);
	Write_Cmd_Data(y1 >> 8);
	Write_Cmd_Data (y1 & 0xff);
	Write_Cmd(0x2C);//LCD_WriteCMD(GRAMWR);
}

//CLEAR SCREEN

void ClearScreen(uint16_t bColor)
{
 int n= ILI9341_WIDTH * ILI9341_HEIGHT; //76800;

	if(rotationNum==1 || rotationNum==3)
	{
		LCD_SetPos(0,ILI9341_WIDTH-1,0,ILI9341_HEIGHT-1);//320x240
	}
	else if(rotationNum==2 || rotationNum==4)
	{
		LCD_SetPos(0,ILI9341_HEIGHT-1,0,ILI9341_WIDTH-1);//320x240
	}
 	 while(n){
		 n--;
		 Write_Data(bColor);
 	 }
 }

void LCD_DrawPixel(uint16_t x, uint16_t y, uint16_t color) {
	LCD_SetPos(x, x, y, y);
	Write_Data(color);
}


void LCD_Fill_Rect(unsigned int x0, unsigned int y0, unsigned int w, unsigned int h, uint16_t color){
	int n= w*h;
	LCD_SetPos(x0, x0+w-1, y0, y0+h-1);
	while(n){
		n--;
		Write_Data(color);
	}
	HAL_Delay(1);
}

void LCD_drawDiagonalLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */
    int x2=x0;
    int y2=y0+1;
    while (1) {
//    	for(int i=0;i<5;i++){
			LCD_SetPos(x0, x0, y0, y0);
			Write_Data(color);
			LCD_SetPos(x2, x2, y2, y2);

//    	}
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; y2 += sy+1;} /* e_xy+e_x > 0 */
        if (e2 <= dx) { err += dx; y0 += sy; x2 += sx+1;} /* e_xy+e_y < 0 */
    }
}

void drawBroadLine(int x0, int y0, int x1, int y1, uint16_t color, int thickness) {
    // Calculate the unit direction vector perpendicular to the line
    float dx = x1 - x0;
    float dy = y1 - y0;
    float length = sqrtf(dx * dx + dy * dy);
    float ux = -dy / length;
    float uy = dx / length;

    // Draw multiple parallel lines to create the broad line effect
    for (int i = -thickness / 2; i <= thickness / 2; i++) {
        int offsetX = (int)(i * ux);
        int offsetY = (int)(i * uy);
        LCD_drawDiagonalLine(x0 + offsetX, y0 + offsetY, x1 + offsetX, y1 + offsetY, color);
    }
}

void LCD_drawFastHLine(int16_t x0, int16_t y0, int16_t w, uint16_t color){
	int n= w;
	LCD_SetPos(x0, x0+w, y0, y0);
	while(n){
		n--;
		Write_Data(color);
	}
	HAL_Delay(1);
}

void LCD_drawFastVLine(int16_t x0, int16_t y0, int16_t h, uint16_t color){
	int n= h;
	LCD_SetPos(x0, x0, y0, y0+h);
	while(n){
		n--;
		Write_Data(color);
	}
	HAL_Delay(1);
}

void swap(uint16_t *a, uint16_t *b) {
    uint16_t temp = *a;
    *a = *b;
    *b = temp;
}

void LCD_drawFilledTriangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
	 // Sort the vertices by y-coordinate ascending (y0 <= y1 <= y2)
	    if (y0 > y1) {
	        swap(&y0, &y1);
	        swap(&x0, &x1);
	    }
	    if (y1 > y2) {
	        swap(&y1, &y2);
	        swap(&x1, &x2);
	    }
	    if (y0 > y1) {
	        swap(&y0, &y1);
	        swap(&x0, &x1);
	    }

	    int16_t dx1, dy1, dx2, dy2, dx3, dy3;
	    dx1 = x1 - x0;
	    dy1 = y1 - y0;
	    dx2 = x2 - x0;
	    dy2 = y2 - y0;
	    dx3 = x2 - x1;
	    dy3 = y2 - y1;

	    int16_t sa = 0, sb = 0;

	    int16_t last = y1 == y2 ? y1 : y1 - 1;
	    int16_t y = y0;
	    for ( y = y0; y <= last; y++) {
	        int16_t a = x0 + sa / dy1;
	        int16_t b = x0 + sb / dy2;
	        if (a > b) swap(&a, &b);
	        LCD_drawFastHLine(a, y, b - a + 1, color);
	        sa += dx1;
	        sb += dx2;
	    }

	    sa = dx3 * (y - y1);
	    sb = dx2 * (y - y0);

	    for (; y <= y2; y++) {
	        int16_t a = x1 + sa / dy3;
	        int16_t b = x0 + sb / dy2;
	        if (a > b) swap(&a, &b);
	        LCD_drawFastHLine(a, y, b - a + 1, color);
	        sa += dx3;
	        sb += dx2;
	    }
}

void LCD_Rect(unsigned int x0,unsigned int y0, unsigned int w,unsigned int h, uint16_t color){
	LCD_drawFastHLine(x0, y0, w, color);
	LCD_drawFastHLine(x0, y0+h-1, w, color);
	LCD_drawFastVLine(x0, y0, h, color);
	LCD_drawFastVLine(x0+w, y0, h, color);
}

void LCD_drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color){
	int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

  LCD_DrawPixel(x0  , y0+r, color);
  LCD_DrawPixel(x0  , y0-r, color);
  LCD_DrawPixel(x0+r, y0  , color);
  LCD_DrawPixel(x0-r, y0  , color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

    LCD_DrawPixel(x0 + x, y0 + y, color);
    LCD_DrawPixel(x0 - x, y0 + y, color);
    LCD_DrawPixel(x0 + x, y0 - y, color);
    LCD_DrawPixel(x0 - x, y0 - y, color);
    LCD_DrawPixel(x0 + y, y0 + x, color);
    LCD_DrawPixel(x0 - y, y0 + x, color);
    LCD_DrawPixel(x0 + y, y0 - x, color);
    LCD_DrawPixel(x0 - y, y0 - x, color);
}
}

void LCD_drawUpperHalfCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color){
	int16_t f = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x = 0;
  int16_t y = r;

//  LCD_DrawPixel(x0  , y0+r, color);
  LCD_DrawPixel(x0  , y0-r, color);
  LCD_DrawPixel(x0+r, y0  , color);
  LCD_DrawPixel(x0-r, y0  , color);

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x;

//    LCD_DrawPixel(x0 + x, y0 + y, color);
//    LCD_DrawPixel(x0 - x, y0 + y, color);
    LCD_DrawPixel(x0 + x, y0 - y, color);
    LCD_DrawPixel(x0 - x, y0 - y, color);
//    LCD_DrawPixel(x0 + y, y0 + x, color);
//    LCD_DrawPixel(x0 - y, y0 + x, color);
    LCD_DrawPixel(x0 + y, y0 - x, color);
    LCD_DrawPixel(x0 - y, y0 - x, color);
}
}

static void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color)
{
	int16_t f     = 1 - r;
  int16_t ddF_x = 1;
  int16_t ddF_y = -2 * r;
  int16_t x     = 0;
  int16_t y     = r;

  while (x<y) {
    if (f >= 0) {
      y--;
      ddF_y += 2;
      f     += ddF_y;
    }
    x++;
    ddF_x += 2;
    f     += ddF_x;

    if (cornername & 0x1) {
    	LCD_drawFastVLine(x0+x, y0-y, 2*y+1+delta, color);
    	LCD_drawFastVLine(x0+y, y0-x, 2*x+1+delta, color);
    }
    if (cornername & 0x2) {
    	LCD_drawFastVLine(x0-x, y0-y, 2*y+1+delta, color);
    	LCD_drawFastVLine(x0-y, y0-x, 2*x+1+delta, color);
    }
  }
}

static inline void _swap_int16_t(int16_t a, int16_t b) {
    int16_t t = a;
    a = b;
    b = t;
}

void ILI9341_DrawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color)
{
    for (int16_t i = 0; i < w; i++) {
    	LCD_DrawPixel(x + i, y, color);
    }
}

void GFX_FillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
{
    int16_t a, b, y, last;
    int16_t dx01, dy01, dx02, dy02, dx12, dy12;
    int32_t sa, sb;

    // Sort coordinates by Y order (y0 <= y1 <= y2)
    if (y0 > y1) { _swap_int16_t(y0, y1); _swap_int16_t(x0, x1); }
    if (y1 > y2) { _swap_int16_t(y2, y1); _swap_int16_t(x2, x1); }
    if (y0 > y1) { _swap_int16_t(y0, y1); _swap_int16_t(x0, x1); }

    if (y0 == y2) { // Handle awkward all-on-same-line case as its own thing
        a = b = x0;
        if (x1 < a)      a = x1;
        else if (x1 > b) b = x1;
        if (x2 < a)      a = x2;
        else if (x2 > b) b = x2;
        ILI9341_DrawFastHLine(a, y0, b-a+1, color);
        return;
    }

    dx01 = x1 - x0;
    dy01 = y1 - y0;
    dx02 = x2 - x0;
    dy02 = y2 - y0;
    dx12 = x2 - x1;
    dy12 = y2 - y1;

    sa = sb = 0;

    if (y1 == y2) last = y1;   // Include y1 scanline
    else          last = y1-1; // Skip it

    for (y = y0; y <= last; y++) {
        a = x0 + sa / dy01;
        b = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        if (a > b) _swap_int16_t(a,b);
        ILI9341_DrawFastHLine(a, y, b-a+1, color);
    }

    sa = dx12 * (y - y1);
    sb = dx02 * (y - y0);
    for (; y <= y2; y++) {
        a = x1 + sa / dy12;
        b = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        if (a > b) _swap_int16_t(a,b);
        ILI9341_DrawFastHLine(a, y, b-a+1, color);
    }
}

void LCD_drawGaugePointer(uint16_t x, uint16_t y, uint16_t radius, float angle, uint16_t color)
{
    // Convert angle to radians
    float rad = (angle) * 3.14159265 / 180.0;

    // Calculate the tip of the pointer
    uint16_t xTip = x + (radius * cos(rad));
    uint16_t yTip = y - (radius * sin(rad));

    // Calculate the base points of the pointer (triangle)
    float baseAngle = 10 * 3.14159265 / 180.0; // Width of the pointer
    uint16_t xBase1 = x + (10 * cos(rad + baseAngle));
    uint16_t yBase1 = y - (10 * sin(rad + baseAngle));
    uint16_t xBase2 = x + (10 * cos(rad - baseAngle));
    uint16_t yBase2 = y - (10 * sin(rad - baseAngle));

    // Draw filled triangle for the pointer
    GFX_FillTriangle(xTip, yTip, xBase1, yBase1, xBase2, yBase2, color);
}

void LCD_fillArc(uint16_t x, uint16_t y, uint16_t radius, uint16_t startAngle, uint16_t endAngle, uint16_t color)
{
    int16_t i, j;
    float startRad = startAngle * 3.14 / 180;
    float endRad = endAngle * 3.14 / 180;

    for (i = 0; i < radius; i++) {
        for (j = startRad * 100; j < endRad * 100; j++) {
            float angle = j / 100.0;
            int16_t xPos = x + i * cos(angle);
            int16_t yPos = y + i * sin(angle);
            LCD_DrawPixel(xPos, yPos, color);
        }
    }
}

void LCD_fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color)
{
	LCD_drawFastVLine(x0, y0-r, 2*r+1, color);

  fillCircleHelper(x0, y0, r, 3, 0, color);
  HAL_Delay(1);
}


void drawPointer(int x0, int y0, int radius, int value, uint16_t color) {
	float angle = (value -180) * (3.14 / 180);
	int x = x0 + (radius - 20) * cos(angle);
	int y = y0 + (radius - 20) * sin(angle);
	int x1 = x0 + (31 - 20) * cos(angle);
	int y1 = y0 + (31 - 20) * sin(angle);
	LCD_drawDiagonalLine(x1, y1, x, y, color);

//     angle = (value -180) * (3.14 / 180);
//     x = x0 + (radius - 20) * cos(angle);
//     y = y0 + (radius - 20) * sin(angle);
//     x1 = x0 + (31 - 20) * cos(angle);
//	 y1 = y0 + (31 - 20) * sin(angle);
//
//	drawBroadLine(x1, y1, x, y, color,1);

}

static void LCD_WriteChar(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor) {
    uint32_t i, b, j;

    LCD_SetPos(x, x+font.width[ch-32]-1, y,  y+font.height-1);

    for(i = 0; i < font.height; i++) {
        b = font.data[(ch - 32) * font.height + i];
        for(j = 0; j < font.width[ch-32]; j++) {
            if((b << j) & 0x80000000)  {
                Write_Data(color);
            } else {
                Write_Data(bgcolor);
            }
        }
    }
}

uint16_t WIDTH;
uint16_t HEIGHT;

uint8_t ILI9341_getRotation(void)
{
	return rotationNum;
}

void LCD_WriteString(uint16_t x, uint16_t y,  uint8_t* str, uint16_t strlength, FontDef font, uint16_t color, uint16_t bgcolor) {
	ILI9341_getRotation();
	if(rotationNum == 1 || rotationNum ==3)
	{
		WIDTH = 240;
		HEIGHT = 320;
	}
	else if (rotationNum == 2 || rotationNum ==4){
		WIDTH = 320;
		HEIGHT = 240;
	}
	while(*str) {

        if(x + font.width[*str-32] >= WIDTH) {
//            x = 0;
//            y += font.height;
        	break;
            if(y + font.height >= HEIGHT) {
                break;
            }

            if(*str == ' ') {
                // skip spaces in the beginning of the new line
                str++;
                continue;
            }
        }

        LCD_WriteChar(x, y, *str, font, color, bgcolor);
        x += font.width[*str-32];
        str++;
    }

}

void LCD_DrawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t* data){
	int n= w*h;
	int i=0;
//	Write_Cmd(0x21);
	LCD_SetPos(x, x+w-1, y, y+h-1);
	while(n){
		n--;
		Write_Data(data[i]);
		i++;
	}

}

void setRotation(uint8_t rotate)
{
	switch(rotate)
	{
		case 0:
			rotationNum = 1;
			Write_Cmd(0x36);
			Write_Cmd_Data(0x48);
			break;
		case 1:
			rotationNum = 2;
			Write_Cmd(0x36);
			Write_Cmd_Data(0xE8);
//			Write_Cmd_Data(0x08);
			break;
		case 2:
			rotationNum = 3;
			Write_Cmd(0x36);
			Write_Cmd_Data(0x88);
			break;
		case 3:
			rotationNum = 4;
			Write_Cmd(0x36);
			Write_Cmd_Data(0x28);
			break;
		default:
			rotationNum = 1;
			Write_Cmd(0x36);
			Write_Cmd_Data(0x48);
			break;
	}
}
