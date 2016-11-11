/**
 * \file
 * \brief Real Time Operating System (RTOS) main program.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#if PL_CONFIG_HAS_RTOS
#include "RTOS.h"
#include "FRTOS1.h"
#include "LED.h"
#include "Event.h"
#include "Keys.h"
#include "Application.h"

SemaphoreHandle_t keyMasterSlave;


static void masterTask(void* param){
	(void)param;
	for(;;){
	FRTOS1_vTaskDelay(10);
	FRTOS1_xSemaphoreGive(keyMasterSlave);
	}
}

static void slaveTask(void* param){
	(void)param;
	for(;;){
	FRTOS1_xSemaphoreTake(keyMasterSlave, portMAX_DELAY);
	LED2_Neg();
	}
}

static void Task1(void* param){
	(void)param;
	for(;;){

		FRTOS1_vTaskDelay(pdMS_TO_TICKS(100));
	}

}
static void MainTask(void* param){
	(void)param;
	for(;;){

	#if PL_CONFIG_HAS_KEYS
    	KEY_Scan();
	#endif
	#if PL_CONFIG_HAS_EVENTS
    	EVNT_HandleEvent(APP_EventHandler, TRUE);
	#endif
    	FRTOS1_vTaskDelay(pdMS_TO_TICKS(50));
	}
}



static void AppTask(void* param) {
  const int *whichLED = (int*)param;

  (void)param; /* avoid compiler warning */
  for(;;) {
    if (*whichLED==1) {
      LED1_Neg();
    } else if (*whichLED==2) {
      LED2_Neg();
    }
    /* \todo handle your application code here */
    FRTOS1_vTaskDelay(pdMS_TO_TICKS(500));

    //CLS1_SendStr("Led toggled\r\n", CLS1_GetStdio()->stdOut);
  }
}

void RTOS_Init(void) {
  static const int led1 = 1;
  static const int led2 = 2;

  EVNT_SetEvent(EVNT_STARTUP); /* set startup event */
  /*! \todo Create tasks here */
  if (FRTOS1_xTaskCreate(AppTask, (signed portCHAR *)"App1", configMINIMAL_STACK_SIZE, (void*)&led1, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error case only, stay here! */
  }

  if (FRTOS1_xTaskCreate(MainTask, (signed portCHAR *)"MainShit", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
        for(;;){} /* error case only, stay here! */
      }

  if (FRTOS1_xTaskCreate(Task1, (signed portCHAR *)"Task1", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
      for(;;){} /* error case only, stay here! */
    }
  	  keyMasterSlave = FRTOS1_xSemaphoreCreateBinary();
  	  FRTOS1_vQueueAddToRegistry(keyMasterSlave, "LedSemaphore");

  if (FRTOS1_xTaskCreate(masterTask, (signed portCHAR *)"masterTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
        for(;;){} /* error case only, stay here! */
      }
  if (FRTOS1_xTaskCreate(slaveTask, (signed portCHAR *)"slaveTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
        for(;;){} /* error case only, stay here! */
      }
}

void RTOS_Deinit(void) {
  /* nothing needed for now */
}

#endif /* PL_CONFIG_HAS_RTOS */
