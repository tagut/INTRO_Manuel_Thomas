/**
 * \file
 * \brief Key/Switch driver implementation.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a generic keyboard driver for up to 7 Keys.
 * It is using macros for maximum flexibility with minimal code overhead.
 */

#include "Platform.h"
#if PL_CONFIG_HAS_KEYS
  #include "Keys.h"
#if PL_CONFIG_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_CONFIG_HAS_DEBOUNCE
  #include "KeyDebounce.h"
#endif
#if PL_CONFIG_BOARD_IS_ROBO_V2
  #include "PORT_PDD.h"
#endif
<<<<<<< HEAD
//                        #include "FreeRTOSConfig.h"
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  #include "SYS1.h"
=======
#if PL_CONFIG_HAS_RTOS
	#include "FreeRTOSConfig.h"
	#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  	  #include "SYS1.h"
	#endif
>>>>>>> f7bbac00e5b363c9fba74f8d9a3a065fbfe7ff33
#endif


void KEY_Scan(void) {
  #if PL_CONFIG_NOF_KEYS >= 1 && !PL_CONFIG_KEY_1_ISR
    if (KEY1_Get()) { /* key pressed */
      EVNT_SetEvent(EVNT_SW1_PRESSED);
    }
  #endif
    /*! \todo check handling all keys */
    int cnt;
#if PL_LOCAL_CONFIG_BOARD_IS_FRDM //Buttons 5-6 with Pulling
    if(KEY5_Get()){
    	WAIT1_Waitms(50);
    	if(KEY5_Get()){
    		cnt = 0;
    		while(KEY5_Get()){
    			WAIT1_Waitms(1);
    			cnt++;
    		}
    		if(cnt<=200){
    			EVNT_SetEvent(EVNT_SW5_PRESSED);
    		}else{
    			EVNT_SetEvent(EVNT_SW5_LONG_PRESSED);
    		}
    	}
    }
    if(KEY6_Get()){
    	WAIT1_Waitms(50);
    	    	if(KEY6_Get()){
    	    		cnt = 0;
    	    		while(KEY6_Get()){
    	    			WAIT1_Waitms(1);
    	    			cnt++;
    	    		}
    	    		if(cnt<=200){
    	    			EVNT_SetEvent(EVNT_SW6_PRESSED);
    	    		}else{
    	    			EVNT_SetEvent(EVNT_SW6_LONG_PRESSED);
    	    		}
    	    	}
     }

#endif

}

void KEY_EnableInterrupts(void) {
#if PL_CONFIG_KEY_1_ISR
  SW1_Enable();
#endif
#if PL_CONFIG_KEY_2_ISR
  SW2_Enable();
#endif
#if PL_CONFIG_KEY_3_ISR
  SW3_Enable();
#endif
#if PL_CONFIG_KEY_4_ISR
  SW4_Enable();
#endif
#if PL_CONFIG_KEY_5_ISR
  SW5_Enable();
#endif
#if PL_CONFIG_KEY_6_ISR
  SW6_Enable();
#endif
#if PL_CONFIG_KEY_7_ISR
  SW7_Enable();
#endif
}

void KEY_DisableInterrupts(void) {
#if PL_CONFIG_KEY_1_ISR
  SW1_Disable();
#endif
#if PL_CONFIG_KEY_2_ISR
  SW2_Disable();
#endif
#if PL_CONFIG_KEY_3_ISR
  SW3_Disable();
#endif
#if PL_CONFIG_KEY_4_ISR
  SW4_Disable();
#endif
#if PL_CONFIG_KEY_5_ISR
  SW5_Disable();
#endif
#if PL_CONFIG_KEY_6_ISR
  SW6_Disable();
#endif
#if PL_CONFIG_KEY_7_ISR
  SW7_Disable();
#endif
}

void KEY_OnInterrupt(KEY_Buttons button) {
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  SYS1_RecordEnterISR();
#endif
#if PL_CONFIG_HAS_DEBOUNCE
  KEYDBNC_Process(); /* debounce key(s) */
#else
  /* no debounce, only setting event */
  switch(button) {
#if PL_CONFIG_NOF_KEYS>=1
    case KEY_BTN1:
      EVNT_SetEvent(EVNT_SW1_PRESSED);
      break;
#endif
#if PL_CONFIG_NOF_KEYS>=2
    case KEY_BTN2:
      EVNT_SetEvent(EVNT_SW2_PRESSED);
      break;
#endif
#if PL_CONFIG_NOF_KEYS>=3
    case KEY_BTN3:
      EVNT_SetEvent(EVNT_SW3_PRESSED);
      break;
#endif
#if PL_CONFIG_NOF_KEYS>=4
    case KEY_BTN4:
      EVNT_SetEvent(EVNT_SW4_PRESSED);
      break;
#endif
#if PL_CONFIG_NOF_KEYS>=5
    case KEY_BTN5:
      EVNT_SetEvent(EVNT_SW5_PRESSED);
      break;
#endif
#if PL_CONFIG_NOF_KEYS>=6
    case KEY_BTN6:
      EVNT_SetEvent(EVNT_SW6_PRESSED);
      break;
#endif
#if PL_CONFIG_NOF_KEYS>=7
    case KEY_BTN7:
      EVNT_SetEvent(EVNT_SW7_PRESSED);
      break;
#endif
    default:
      break;
  }
#endif
#if configUSE_SEGGER_SYSTEM_VIEWER_HOOKS
  SYS1_RecordExitISR();
#endif
}


/*! \brief Key driver initialization */
void KEY_Init(void) {
#if PL_CONFIG_BOARD_IS_ROBO_V2
  /* enable and turn on pull-up resistor for PTA14 */
  PORT_PDD_SetPinPullSelect(PORTA_BASE_PTR, 14, PORT_PDD_PULL_UP);
  PORT_PDD_SetPinPullEnable(PORTA_BASE_PTR, 14, PORT_PDD_PULL_ENABLE);
#endif
}

/*! \brief Key driver de-initialization */
void KEY_Deinit(void) {
  /* nothing needed for now */
}
#endif /* PL_HAS_KEYS */
