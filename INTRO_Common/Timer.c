/**
 * \file
 * \brief Timer driver
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements the driver for all our timers.
  */

#include "Platform.h"
#if PL_CONFIG_HAS_TIMER
#include "Timer.h"
#if PL_CONFIG_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_CONFIG_HAS_TRIGGER
  #include "Trigger.h"
#endif
#if PL_CONFIG_HAS_MOTOR_TACHO
  #include "Tacho.h"
#endif

#define TMR_HARTBEAT 1000 //Time in MS

void TMR_OnInterrupt(void) {
  /* this one gets called from an interrupt!!!! */
  /*! \todo Add code for a blinking LED here */
	static uint8 counter = 0;
	counter ++;
	if(counter >= TMR_HARTBEAT/TMR_TICK_MS){
		EVNT_SetEvent(EVNT_LED_HEARTBEAT);
		counter = 0;
	}
#if PL_CONFIG_HAS_TRIGGER
		TRG_AddTick();
#endif
}

void TMR_Init(void) {
}

void TMR_Deinit(void) {
}

#endif /* PL_CONFIG_HAS_TIMER*/
