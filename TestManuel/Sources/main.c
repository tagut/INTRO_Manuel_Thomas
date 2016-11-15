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
#include "UTIL1.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "CLS1.h"
#include "CS2.h"
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
  //CLS1_SendStr("HALLO MANUEL",CLS1_GetStdio()->stdOut);

  //Uart LOOP Back for Testing TMP....
  static uint8_t BUF[15000];
  for(int i = 0;i<15000;i++){
	  BUF[i] = 'A';
  }
  int send = 0;
  uint8_t *bufer = BUF;
  int recive = 0;
  for(send = 0;send<15000;send++){

	  //while(!AS1_GetCharsInRxBuf()){}
	//while(!CLS1_KeyPressed()){}
	  CLS1_ReadChar(BUF+send);
	while('\0' == *(BUF+send)){
		CLS1_ReadChar(BUF+send);
	}
		  //AS1_RecvChar(BUF+send);
	  /*size_t hallo = 5;
	  uint8_t buffer = 0;
	  CLS1_ReadLine(buffer,buffer,5,&CLS1_GetStdio()->stdOut);
	  while(!(CLS1_ReadLine(bufer,bufer,hallo,(CLS1_GetStdio()->stdIn)))){}
	  bufer += 4;
	  */
	  if(send == (15000-1)){
		  WAIT1_Waitms(5000);

		  for(recive = 0;recive < 15000;recive++){
			  //AS1_SendChar(BUF[recive]);
			  CLS1_SendChar(BUF[recive]);
			  WAIT1_Waitms(1);
			  send = 0;
			  CLS1_ReadChar(BUF+send); //CLEAR BUFFER

		  }
	  }

  }
/*
  int jumper = 0;



  //Batterie
  	  int SOC = 5;

  C12864_init(); //Display

  for(;;){
	  char halloWelt[] = {"AMZ pilatus"};
	  char zeit[] = {"1:50:23"};
	  char runde[] = {"1:30:22"};
	  FDisp1_PixelDim x = 5;
	  FDisp1_PixelDim y = 5;

	  GDisp1_Clear();

	  FDisp1_WriteString(halloWelt,GDisp1_COLOR_PIXEL_SET,&x,&y,GFONT1_GetFont());
	  x = 5;
	  y = 20;
	  FDisp1_WriteString(zeit,GDisp1_COLOR_PIXEL_SET,&x,&y,GFONT1_GetFont());
	  x = 5;
	  y = 40;
	  FDisp1_WriteString(runde,GDisp1_COLOR_PIXEL_SET,&x,&y,GFONT1_GetFont());
	  //GFONT_Callbacks gibt einen Poiter zurück



	  GDisp1_DrawBox(90,5,20,48,1,1);
	  for(int i = 0;i<SOC;i++){
	  	GDisp1_DrawFilledBox(92,43-(i*9),16,8,1);//Balken ganz unten
	  }
	  if(SOC == 0){
		  SOC = 5+1;
	  }
	  SOC--;

	  WAIT1_Waitms(500); //2s

	  //jumper ++;
	  //GDisp1_DrawFilledBox(30,jumper,30,30,GDisp1_COLOR_PIXEL_SET);
	  C12864_UpdateFull();

	  if(jumper == 64){
		  jumper = 0;
	  }

	  //WAIT1_Waitms(100); //2s

	  //WAIT1_Waitms(10000); //10s
  }
  */

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
