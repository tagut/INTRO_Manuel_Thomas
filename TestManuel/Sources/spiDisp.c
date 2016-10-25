/*
 * spiDisp.c
 *
 *  Created on: 25.10.2016
 *      Author: Manuel
 */

#include "spiDisp.h"
#include "wait1.h"
#include "insData.h"


void Command(){

}

void Write(){

}

void init(){
	WAIT1_Waitms(100);
	insData_ClrVal();
	SM1_SendChar(0xA0);//Display Normal
	SM1_SendChar(0xAE);//Display OFF
	SM1_SendChar(0xC0);//Common output mode select
	SM1_SendChar(0xA2);//LCD Bias Voltage Ratio 1/9 Richtig ???
	SM1_SendChar(0x2F);//Select internal power supply operation Mode ??
	SM1_SendChar(0x26);//Select internal resistor ratio (Rb/Ra) mode
	SM1_SendChar(0x81);//Set the V5 output voltage electronic volume register
	SM1_SendChar(0x11);//Set the most significant 4 bits of the display Ram colum address
	SM1_SendChar(0xAF);//Display ON

	SM1_SendChar(0xE3);//NOP

	SM1_SendChar(0x40);//Display Start Adress 0

	for(;;){
//Page 0 -> Ganz unten -> von unten nach oben
	SM1_SendChar(0xB1);//Page set Adress 0
	SM1_SendChar(0x10);// High bits Column
	SM1_SendChar(0x00); //Low Bits --> Adress 0
	SM1_SendChar(0xE0);//Read/Modify/Write

	//SM1_SendChar(0xA5);//All on
	//SM1_SendChar(0xA4);//All on -> normal mode


	insData_SetVal();

	for(int i=0;i<550;i++){
		//insData_SetVal();
		//WAIT1_Waitms(1);
		SM1_SendChar(0x8F);//Random  MSB -> oberstes  somit von unten nach oben
	/*SM1_SendChar(0x00);//Random
	SM1_SendChar(0x00);//Random
	SM1_SendChar(0xBC);//Random
	SM1_SendChar(0x5C);//Random
	*/
	}
	insData_ClrVal();
	SM1_SendChar(0xEE);//END
	SM1_SendChar(0xAE);//Display OFF
	SM1_SendChar(0xAF);//Display ON

	}


}






