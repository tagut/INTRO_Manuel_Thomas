/* ###################################################################
**     Filename    : main.c
**     Project     : FRDM
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-09-30, 13:14, # CodeGen: 0
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
#include "Cpu.h"
#include "Events.h"
#include "SW1.h"
#include "ExtIntLdd1.h"
#include "SW2.h"
#include "ExtIntLdd2.h"
#include "SW3.h"
#include "ExtIntLdd3.h"
#include "SW4.h"
#include "ExtIntLdd4.h"
#include "SW5.h"
#include "BitIoLdd5.h"
#include "SW6.h"
#include "BitIoLdd6.h"
#include "SW7.h"
#include "ExtIntLdd5.h"
#include "WAIT1.h"
#include "UTIL1.h"
#include "KSDK1.h"
#include "HF1.h"
#include "CS1.h"
#include "KIN1.h"
#include "LEDpin1.h"
#include "BitIoLdd10.h"
#include "LEDPin2.h"
#include "BitIoLdd11.h"
#include "LEDPin3.h"
#include "BitIoLdd12.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "CLS1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Event.h"
#include "Application.h"
#include "Event.h"


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example:*/
  EVNT_Init();
  for(;;) {
	  /*
	  LEDPin1_SetVal();
	  if(CLS1_KeyPressed()){
		  LEDPin1_ClrVal();
	  }
	  char temp[100];
	  uint8_t hallo;
	  CLS1_ReadChar(&hallo);
	  WAIT1_Waitms(100);
	  //CLS1_SendCh();
	  //CLS1_SendChar(hallo);
	  CLS1_SendCh(hallo,CLS1_GetStdio()->stdOut);
	   */


	  //if(CLS1_ReadLine(temp,temp,100,CLS1_GetStdio())){
	//	  CLS1_SendStr((uint8_t)temp,CLS1_GetStdio());
	 // }
	  APP_Start();

	  //WAIT1_Waitms(100);
	  //EVNT_HandleEvent((*APP_HandleEvent),1);
	  //WAIT1_Waitms(100);


/*
	  int i[10];
	  int* ia = NULL;
	  LEDPin1_ClrVal();
	  WAIT1_Waitms(1000);
	  CS1_EnterCritical();

	  LEDPin1_SetVal();
	  CS1_ExitCritical();
	  LEDPin2_ClrVal();
	  i[1245523] = 100 ;
	  WAIT1_Waitms(1000);
	  LEDPin2_SetVal();
	  LEDPin3_ClrVal();
	  WAIT1_Waitms(1000);
	  LEDPin3_SetVal();
*/

  }

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