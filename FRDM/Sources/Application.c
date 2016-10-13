/*
 * Application.c
 *
 *  Created on: 13.10.2016
 *      Author: Manuel
 */
#include "Application.h"
#include "LEDPin1.h"



void APP_HandleEvent(EVNT_Handle event){
	if(event == EVNT_LED_HEARTBEAT){
		LEDPin1_NegVal();
	}

}

