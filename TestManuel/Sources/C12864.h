/*
 * spiDisp.h
 *
 *  Created on: 25.10.2016
 *      Author: Manuel
 */

#ifndef SOURCES_C12864_H_
#define SOURCES_C12864_H_


#include "SM1.h"

//Aus Styger KentchLCD

#define C12864_DISPLAY_HW_NOF_COLUMNS  128u /* we have 128 columns in hardware */
#define C12864_DISPLAY_HW_NOF_ROWS     64u /* we have 64 rows in hardware */

extern byte C12864_DisplayBuf[C12864_DISPLAY_HW_NOF_ROWS/8][C12864_DISPLAY_HW_NOF_COLUMNS]; /* display buffer */

typedef bool C12864_PixelColor;        /* one bit is enough to describe the color as we have a monochrome display */
typedef byte C12864_PixelDim;          /* one byte is enough to describe an x/y position */

#define C12864_PIXEL_WHITE  1          /* 1 is a white pixel */
#define C12864_PIXEL_BLACK   0          /* 0 is a blue pixel */
#define C12864_COLOR_PIXEL_SET      C12864_PIXEL_WHITE /* color for a pixel set */
#define C12864_COLOR_PIXEL_CLR      C12864_PIXEL_BLACK /* color for a pixel cleared */
#define C12864_COLOR_BLACK          C12864_PIXEL_BLACK
#define C12864_COLOR_WHITE          C12864_PIXEL_WHITE
#define C12864_COLOR_RED            C12864_COLOR_BLACK
#define C12864_COLOR_BRIGHT_RED     C12864_COLOR_WHITE
#define C12864_COLOR_DARK_RED       C12864_COLOR_BLACK
#define C12864_COLOR_GREEN          C12864_COLOR_BLACK
#define C12864_COLOR_BRIGHT_GREEN   C12864_COLOR_WHITE
#define C12864_COLOR_DARK_GREEN     C12864_COLOR_BLACK
#define C12864_COLOR_BLUE           C12864_COLOR_BLACK
#define C12864_COLOR_BRIGHT_BLUE    C12864_COLOR_WHITE
#define C12864_COLOR_DARK_BLUE      C12864_COLOR_BLACK
#define C12864_COLOR_YELLOW         C12864_COLOR_BLACK
#define C12864_COLOR_BRIGHT_YELLOW  C12864_COLOR_WHITE
#define C12864_COLOR_ORANGE         C12864_COLOR_BLACK
#define C12864_COLOR_GREY           C12864_COLOR_BLACK
#define C12864_COLOR_BRIGHT_GREY    C12864_COLOR_WHITE

typedef enum {
  C12864_ORIENTATION_PORTRAIT    = 0,
  C12864_ORIENTATION_PORTRAIT180 = 1,
  C12864_ORIENTATION_LANDSCAPE   = 2,
  C12864_ORIENTATION_LANDSCAPE180= 3
} C12864_DisplayOrientation;

#define C12864_HW_WIDTH         128u   /* width of display in pixels */
#define C12864_HW_HEIGHT        64u    /* height of display in pixels */

#define C12864_HW_SHORTER_SIDE  64u    /* size of shorter display side in pixels */
#define C12864_HW_LONGER_SIDE   128u   /* size of longer display side in pixels */



#ifndef __BWUserType_C12864_PixelCount
#define __BWUserType_C12864_PixelCount
  typedef word C12864_PixelCount ;     /* A word is enough to count all pixels of the display. */
#endif

  //Manuel

#define C12864_GetShorterSide \
		C12864_HW_SHORTER_SIDE

#define C12864_GetLongerSide \
		C12864_HW_LONGER_SIDE




  void C12864_UpdateFull();

  void C12864_UpdateRegion(C12864_PixelDim x,C12864_PixelDim y,C12864_PixelDim w,C12864_PixelDim h);


  void C12864_init();




#endif /* SOURCES_C12864_H_ */
