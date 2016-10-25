/* ###################################################################
**     Filename    : main.c
**     Project     : TestManuel
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-09-22, 15:42, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include <C12864.h>
#include "Cpu.h"
#include "Events.h"
#include "WAIT1.h"
#include "KSDK1.h"
#include "SM1.h"
#include "SMasterLdd1.h"
#include "insData.h"
#include "BitIoLdd1.h"
#include "GDisp1.h"
#include "ChLCD1.h"
#include "CS1.h"
#include "BitIoLdd2.h"
#include "ChLCDReset1.h"
#include "BitIoLdd3.h"
#include "DataCmd1.h"
#include "BitIoLdd4.h"
#include "Busy1.h"
#include "BitIoLdd5.h"
#include "Vcc1.h"
#include "BitIoLdd6.h"
#include "SPI1.h"
#include "Clock1.h"
#include "BitIoLdd7.h"
#include "Output1.h"
#include "BitIoLdd8.h"
#include "GFONT1.h"
#include "FDisp1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  for(;;){
	  C12864_init(); //Display
	  WAIT1_Waitms(500);
	  char halloWelt[] = {"HalloWelt"};
	  FDisp1_PixelDim x = 5;
	  FDisp1_PixelDim y = 5;

	  FDisp1_WriteString(halloWelt,GDisp1_COLOR_PIXEL_SET,&x,&y,GFONT1_GetFont());
	  C12864_UpdateFull();
	  //GFONT_Callbacks gibt einen Poiter zurück

	  WAIT1_Waitms(2000); //2s

	  GDisp1_DrawFilledBox(30,30,30,30,GDisp1_COLOR_PIXEL_SET);
	  C12864_UpdateFull();

	  //WAIT1_Waitms(10000); //10s
  }

  /* For example: for(;;) { } */

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
