/**
 * \file
 * \brief Module to handle the LCD display
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module is driving the Nokia LCD Display.
 */

#include "Platform.h"
#if PL_CONFIG_HAS_LCD
#include "LCD.h"
#include "PDC1.h"
#include "GDisp1.h"
#include "GFONT1.h"
#include "FDisp1.h"
#include "Application.h"
#include "UTIL1.h"
#include "LCD_LED.h"
#include "Event.h"
#include "FRTOS1.h"
#include "RApp.h"
#include "LCDMenu.h"

/* status variables */
static bool LedBackLightisOn = TRUE;
bool JoystickIsOn = FALSE;
static bool requestLCDUpdate = FALSE;
uint8 SpeedValueMenue = 0;
uint8 SpeedLineValueMenue = 0;

static uint8 test = 0;


/* this type is declared in PE_Types.h for non-LDD processors, need to declare it locally otherwise */
//typedef struct {                       /* Image */
//  word width;                          /* Image width  */
//  word height;                         /* Image height */
//  const byte * pixmap;                 /* Image pixel bitmap */
//  word size;                           /* Image size   */
//  const char_t * name;                 /* Image name   */
//} TIMAGE;
//typedef TIMAGE* PIMAGE ;               /* Pointer to image */
TIMAGE smily;

byte pixelSmily[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
		,0x00,0x00,0x00,0x00,0x03,0xf8,0x00,0x00,0x00,0x00,0x00
		,0x00,0x00,0x00,0x07,0xe0,0x00,0x7e,0x00,0x00,0x00,0x00
		,0x00,0x00,0x00,0x70,0x00,0x00,0x01,0xe0,0x00,0x00,0x00
		,0x00,0x00,0x03,0x80,0x00,0x00,0x00,0x1c,0x00,0x00,0x00
		,0x00,0x00,0x1c,0x00,0x00,0x00,0x00,0x03,0x80,0x00,0x00
		,0x00,0x00,0x60,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x00
		,0x00,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x18,0x00,0x00
		,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00
		,0x00,0x08,0x00,0x03,0xc0,0x00,0x3c,0x00,0x03,0x00,0x00
		,0x00,0x30,0x00,0x0c,0x30,0x00,0xc3,0x00,0x00,0xc0,0x00
		,0x00,0x60,0x00,0x10,0x18,0x01,0x81,0x80,0x00,0x60,0x00
		,0x00,0x80,0x00,0x30,0x0c,0x03,0x00,0xc0,0x00,0x30,0x00
		,0x01,0x00,0x00,0x20,0x0c,0x03,0x00,0x40,0x00,0x18,0x00
		,0x02,0x00,0x00,0x00,0x00,0x02,0x00,0x40,0x00,0x0c,0x00
		,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00
		,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00
		,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00
		,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00
		,0x10,0xfe,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0xf1,0x80
		,0x10,0xd8,0x7f,0xc0,0x00,0x00,0x00,0x7f,0xe1,0xb0,0x80
		,0x10,0xd0,0x06,0x03,0xff,0xff,0xfe,0x06,0x01,0xb0,0x80
		,0x30,0x50,0x06,0x01,0x80,0x60,0x18,0x06,0x01,0xe0,0xc0
		,0x30,0x78,0x06,0x01,0x80,0x60,0x18,0x06,0x01,0xe0,0xc0
		,0x30,0x7c,0x06,0x01,0x80,0x60,0x18,0x06,0x03,0xe0,0xc0
		,0x30,0x77,0xff,0x01,0x80,0x60,0x18,0x0f,0xff,0xe0,0xc0
		,0x10,0x30,0x01,0xff,0xff,0xff,0xff,0xf8,0x00,0xc0,0x80
		,0x10,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x80
		,0x18,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x81,0x80
		,0x18,0x18,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x81,0x00
		,0x08,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x03,0x00
		,0x0c,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x02,0x00
		,0x06,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x00
		,0x02,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0x0c,0x00
		,0x01,0x01,0x80,0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00
		,0x00,0x80,0xe0,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00
		,0x00,0x60,0x7f,0xf8,0x00,0x00,0x03,0xff,0xe0,0x60,0x00
		,0x00,0x30,0x1e,0x0f,0xff,0xff,0xfe,0x07,0x80,0xc0,0x00
		,0x00,0x18,0x0e,0x01,0x80,0x60,0x18,0x07,0x03,0x00,0x00
		,0x00,0x06,0x03,0x81,0x80,0x60,0x18,0x0c,0x06,0x00,0x00
		,0x00,0x01,0x80,0xe1,0x80,0x60,0x18,0x38,0x18,0x00,0x00
		,0x00,0x00,0x60,0x1f,0x80,0x60,0x19,0xc0,0x60,0x00,0x00
		,0x00,0x00,0x1c,0x03,0xc0,0x60,0x1e,0x03,0x80,0x00,0x00
		,0x00,0x00,0x03,0x80,0x1f,0xff,0xc0,0x1c,0x00,0x00,0x00
		,0x00,0x00,0x00,0x78,0x00,0x00,0x01,0xe0,0x00,0x00,0x00
		,0x00,0x00,0x00,0x07,0xe0,0x00,0x7e,0x00,0x00,0x00,0x00
		,0x00,0x00,0x00,0x00,0x03,0xfc,0x00,0x00,0x00,0x00,0x00
		,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

byte pixelMittelfinger[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x03,0xfe,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x0f,0x03,0x80,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x1c,0x38,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x19,0x06,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x1d,0x06,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x1d,0xfe,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x1c,0x78,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x1c,0x00,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x0c,0x00,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x0c,0x00,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x0c,0xf8,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x0c,0x00,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x0c,0x00,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x1c,0x00,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x1c,0x00,0x40,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x1c,0x00,0x40,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x1c,0x00,0x40,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x1c,0x00,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x1c,0xf8,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x1c,0x3e,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x1c,0x00,0xff,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x1c,0x00,0xff,0xe0,0x00,0x00,0x00
,0x00,0x00,0x00,0x03,0xdc,0x00,0xc1,0xf0,0x00,0x00,0x00
,0x00,0x00,0x18,0x1f,0xfe,0x00,0xc0,0x7e,0x00,0x00,0x00
,0x00,0x01,0xff,0xf8,0x1e,0x00,0xc0,0x3f,0xc0,0x00,0x00
,0x00,0x03,0x81,0xe0,0x0e,0x00,0xc0,0x1f,0xf0,0x00,0x00
,0x00,0x07,0x00,0xe0,0x0e,0x01,0xc0,0x1c,0x7c,0x00,0x00
,0x00,0x06,0x00,0xe0,0x0e,0x01,0xc0,0x1c,0x1e,0x00,0x00
,0x00,0x0e,0x00,0xe0,0x0c,0x01,0xc0,0x1c,0x0e,0x00,0x00
,0x00,0x0c,0x00,0xe0,0x0c,0x01,0xc0,0x1c,0x07,0x00,0x00
,0x00,0x0c,0x00,0xc0,0x1c,0x01,0xc0,0x1f,0x07,0x00,0x00
,0x00,0x1c,0x00,0xc0,0x1c,0x01,0xc0,0x0f,0x07,0x00,0x00
,0x00,0x18,0x00,0xc0,0x1c,0x01,0x80,0x0e,0x07,0x80,0x00
,0x00,0x18,0x00,0xc0,0x1c,0x01,0x80,0x0f,0xc7,0x80,0x00
,0x00,0x18,0x00,0xc0,0x3c,0x01,0x80,0x0f,0xc7,0x80,0x00
,0x00,0x1c,0x00,0xc0,0x1c,0x03,0x80,0x0e,0x07,0x80,0x00
,0x00,0x1c,0x00,0x40,0x0c,0x03,0x80,0x00,0x07,0x80,0x00
,0x00,0x1c,0x00,0x00,0x04,0x01,0x00,0x00,0x07,0x80,0x00
,0x00,0x0e,0x02,0x00,0x00,0x00,0x00,0x00,0x0f,0x00,0x00
,0x00,0x06,0x07,0x00,0x00,0x00,0x00,0x00,0x3e,0x00,0x00
,0x00,0x07,0xff,0x00,0x00,0x00,0x00,0x00,0x70,0x00,0x00
,0x00,0x01,0xff,0x80,0x30,0x00,0x00,0x03,0xe0,0x00,0x00
,0x00,0x00,0x03,0xc0,0x38,0x00,0x3f,0xff,0x00,0x00,0x00
,0x00,0x00,0x00,0xff,0xfc,0x00,0xff,0xe0,0x00,0x00,0x00
,0x00,0x00,0x00,0x0f,0x8f,0x87,0xc0,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x03,0xfe,0x00,0x00,0x00,0x00,0x00
,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};




#if PL_CONFIG_HAS_LCD_MENU
typedef enum {
  LCD_MENU_ID_NONE = LCDMENU_ID_NONE, /* special value! */
  LCD_MENU_ID_MAIN,
    LCD_MENU_ID_BACKLIGHT,
    LCD_MENU_ID_NUM_VALUE,
LCD_MENU_ID_Joystick,
	LCD_MENU_ID_Joystick_ON,
	LCD_MENU_ID_Speed,
	LCD_MENU_ID_SpeedLine,
	LCD_MENU_ID_Test,
LCD_MENU_ID_LCD,
	LCD_MENU_ID_Smily,
	LCD_MENU_ID_MittelFinger

} LCD_MenuIDs;

static LCDMenu_StatusFlags ValueChangeHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {
  static int value = 0;
  static uint8_t valueBuf[16];
  LCDMenu_StatusFlags flags = LCDMENU_STATUS_FLAGS_NONE;

  (void)item;
  if (event==LCDMENU_EVENT_GET_TEXT) {
    UTIL1_strcpy(valueBuf, sizeof(valueBuf), (uint8_t*)"Val: ");
    UTIL1_strcatNum32s(valueBuf, sizeof(valueBuf), value);
    *dataP = valueBuf;
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  } else if (event==LCDMENU_EVENT_GET_EDIT_TEXT) {
    UTIL1_strcpy(valueBuf, sizeof(valueBuf), (uint8_t*)"[-] ");
    UTIL1_strcatNum32s(valueBuf, sizeof(valueBuf), value);
    UTIL1_strcat(valueBuf, sizeof(valueBuf), (uint8_t*)" [+]");
    *dataP = valueBuf;
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  } else if (event==LCDMENU_EVENT_DECREMENT) {
    value--;
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  } else if (event==LCDMENU_EVENT_INCREMENT) {
    value++;
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  }
  return flags;
}

static LCDMenu_StatusFlags SpeedLineChangeHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {

  static uint8_t valueBuf[16];
  LCDMenu_StatusFlags flags = LCDMENU_STATUS_FLAGS_NONE;

  (void)item;
  if (event==LCDMENU_EVENT_GET_TEXT) {
    UTIL1_strcpy(valueBuf, sizeof(valueBuf), (uint8_t*)"SpeedLine: ");
    UTIL1_strcatNum32s(valueBuf, sizeof(valueBuf), SpeedLineValueMenue);
    *dataP = valueBuf;
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  } else if (event==LCDMENU_EVENT_GET_EDIT_TEXT) {
    UTIL1_strcpy(valueBuf, sizeof(valueBuf), (uint8_t*)"[-] ");
    UTIL1_strcatNum32s(valueBuf, sizeof(valueBuf), SpeedLineValueMenue);
    UTIL1_strcat(valueBuf, sizeof(valueBuf), (uint8_t*)" [+]");
    *dataP = valueBuf;
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  } else if (event==LCDMENU_EVENT_DECREMENT) {
	  SpeedLineValueMenue--;
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  } else if (event==LCDMENU_EVENT_INCREMENT) {
	  SpeedLineValueMenue++;
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  }
  return flags;
}

static LCDMenu_StatusFlags SpeedChangeHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {

  static uint8_t valueBuf[16];
  LCDMenu_StatusFlags flags = LCDMENU_STATUS_FLAGS_NONE;

  (void)item;
  if (event==LCDMENU_EVENT_GET_TEXT) {
    UTIL1_strcpy(valueBuf, sizeof(valueBuf), (uint8_t*)"Speed: ");
    UTIL1_strcatNum32s(valueBuf, sizeof(valueBuf), SpeedValueMenue);
    *dataP = valueBuf;
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  } else if (event==LCDMENU_EVENT_GET_EDIT_TEXT) {
    UTIL1_strcpy(valueBuf, sizeof(valueBuf), (uint8_t*)"[-] ");
    UTIL1_strcatNum32s(valueBuf, sizeof(valueBuf), SpeedValueMenue);
    UTIL1_strcat(valueBuf, sizeof(valueBuf), (uint8_t*)" [+]");
    *dataP = valueBuf;
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  } else if (event==LCDMENU_EVENT_DECREMENT) {
    SpeedValueMenue--;
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  } else if (event==LCDMENU_EVENT_INCREMENT) {
    SpeedValueMenue++;
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  }
  return flags;
}

static LCDMenu_StatusFlags BackLightMenuHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {
  LCDMenu_StatusFlags flags = LCDMENU_STATUS_FLAGS_NONE;

  (void)item;
  if (event==LCDMENU_EVENT_GET_TEXT && dataP!=NULL) {
    if (LedBackLightisOn) {
      *dataP = "Backlight is ON";
    } else {
      *dataP = "Backlight is OFF";
    }
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  } else if (event==LCDMENU_EVENT_ENTER) { /* toggle setting */
    LedBackLightisOn = !LedBackLightisOn;
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  }
  return flags;
}

void ReachedPoint(char point){
	#if PL_CONFIG_CONTROL_SENDER

		uint8_t buf[2];
		buf[0] = 12;
		buf[1] = (uint8_t)point;
		(void)RAPP_SendPayloadDataBlock(buf, sizeof(buf), 0xAC, 0x12 , RPHY_PACKET_FLAGS_REQ_ACK);//RNETA_GetDestAddr()
	#endif
}


static LCDMenu_StatusFlags MittelFingerMenuHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {
  LCDMenu_StatusFlags flags = LCDMENU_STATUS_FLAGS_NONE;

  (void)item;
  if (event==LCDMENU_EVENT_GET_TEXT && dataP!=NULL) {
	  dataP = "Mittel finger";
	      /*if (JoystickIsOn) {
	        *dataP = "Joystick is ON";
	      } else {
	        *dataP = "Joystick is OFF";
	      }*/
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  } else if (event==LCDMENU_EVENT_ENTER) { /* toggle setting */
	  DrawMittelfinger();
	  /*
	  JoystickIsOn = !JoystickIsOn;
	  if(JoystickIsOn){
		  Button_Pressed('G'); //MANUEL THOMAS  //START
		  for(uint8 test = 0;test<SpeedValueMenue;test++){
			  Button_Pressed('B'); //MANUEL THOMAS  //Speed up
		  }

		  ReachedPoint('A');
	  }else{
		  Button_Pressed('F'); //MANUEL THOMAS  //Stop
	  }
	  */
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  }
  return flags;
}

static LCDMenu_StatusFlags SmilyMenuHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {
  LCDMenu_StatusFlags flags = LCDMENU_STATUS_FLAGS_NONE;

  (void)item;
  if (event==LCDMENU_EVENT_GET_TEXT && dataP!=NULL) {
	  dataP = "Smily";
    /*if (JoystickIsOn) {
      *dataP = "Joystick is ON";
    } else {
      *dataP = "Joystick is OFF";
    }*/
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  } else if (event==LCDMENU_EVENT_ENTER) { /* toggle setting */
	  DrawSmily();
	  /*
	  JoystickIsOn = !JoystickIsOn;
	  if(JoystickIsOn){
		  Button_Pressed('G'); //MANUEL THOMAS  //START
		  for(uint8 test = 0;test<SpeedValueMenue;test++){
			  Button_Pressed('B'); //MANUEL THOMAS  //Speed up
		  }

		  ReachedPoint('A');
	  }else{
		  Button_Pressed('F'); //MANUEL THOMAS  //Stop
	  }
	  */
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  }
  return flags;
}


static LCDMenu_StatusFlags JoystickMenuHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {
  LCDMenu_StatusFlags flags = LCDMENU_STATUS_FLAGS_NONE;

  (void)item;
  if (event==LCDMENU_EVENT_GET_TEXT && dataP!=NULL) {
    if (JoystickIsOn) {
      *dataP = "Joystick is ON";
    } else {
      *dataP = "Joystick is OFF";
    }
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  } else if (event==LCDMENU_EVENT_ENTER) { /* toggle setting */
	  JoystickIsOn = !JoystickIsOn;
	  if(JoystickIsOn){
		  Button_Pressed('G'); //MANUEL THOMAS  //START
		  for(uint8 test = 0;test<SpeedValueMenue;test++){
			  Button_Pressed('B'); //MANUEL THOMAS  //Speed up
		  }
		  for(uint8 test = 0;test<SpeedLineValueMenue;test++){
		  	  Button_Pressed('H'); //MANUEL THOMAS  //Speed up
		  }

		  ReachedPoint('A');
	  }else{
		  Button_Pressed('F'); //MANUEL THOMAS  //Stop
	  }
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  }
  return flags;
}

static LCDMenu_StatusFlags JoystickTestHandler(const struct LCDMenu_MenuItem_ *item, LCDMenu_EventType event, void **dataP) {
  LCDMenu_StatusFlags flags = LCDMENU_STATUS_FLAGS_NONE;

  (void)item;
  if (event==LCDMENU_EVENT_GET_TEXT && dataP!=NULL) {
    /*if (JoystickIsOn) {
      *dataP = "Joystick is ON";
    } else {
      *dataP = "Joystick is OFF";
    }*/
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  } else if (event==LCDMENU_EVENT_ENTER) { /* toggle setting */
	  ReachedPoint('T'); //Send Test
	  Button_Pressed('I'); //Test on Robot
	  /*
	  JoystickIsOn = !JoystickIsOn;
	  if(JoystickIsOn){
		  Button_Pressed('G'); //MANUEL THOMAS  //START
		  for(uint8 test = 0;test<SpeedValueMenue;test++){
			  Button_Pressed('B'); //MANUEL THOMAS  //Speed up
		  }
		  for(uint8 test = 0;test<SpeedLineValueMenue;test++){
		  	  Button_Pressed('H'); //MANUEL THOMAS  //Speed up
		  }

		  ReachedPoint('A');
	  }else{
		  Button_Pressed('F'); //MANUEL THOMAS  //Stop
	  }
	  */
    flags |= LCDMENU_STATUS_FLAGS_HANDLED|LCDMENU_STATUS_FLAGS_UPDATE_VIEW;
  }
  return flags;
}

static const LCDMenu_MenuItem menus[] =
{/* id,                                     grp, pos,   up,                       down,                             text,           callback                      flags                  */
    {LCD_MENU_ID_MAIN,                        0,   0,   LCD_MENU_ID_NONE,         LCD_MENU_ID_BACKLIGHT,            "General",      NULL,                         LCDMENU_MENU_FLAGS_NONE},
      {LCD_MENU_ID_BACKLIGHT,                 1,   0,   LCD_MENU_ID_MAIN,         LCD_MENU_ID_NONE,                 NULL,           BackLightMenuHandler,         LCDMENU_MENU_FLAGS_NONE},
      {LCD_MENU_ID_NUM_VALUE,                 1,   1,   LCD_MENU_ID_MAIN,         LCD_MENU_ID_NONE,                 NULL,           ValueChangeHandler,           LCDMENU_MENU_FLAGS_EDITABLE},
	{LCD_MENU_ID_Joystick,                    0,   1,   LCD_MENU_ID_NONE,         LCD_MENU_ID_Joystick_ON,            "Joystick",      NULL,                         LCDMENU_MENU_FLAGS_NONE},
	  {LCD_MENU_ID_Joystick_ON,               2,   1,   LCD_MENU_ID_Joystick,         LCD_MENU_ID_NONE,                 NULL,           JoystickMenuHandler,           LCDMENU_MENU_FLAGS_NONE},
	  {LCD_MENU_ID_Test,          		      2,   2,   LCD_MENU_ID_Joystick,         LCD_MENU_ID_NONE,            "Test Network",           JoystickTestHandler,           LCDMENU_MENU_FLAGS_NONE},
	  {LCD_MENU_ID_Speed,                     2,   3,   LCD_MENU_ID_Joystick,         LCD_MENU_ID_NONE,                 NULL,           SpeedChangeHandler,           LCDMENU_MENU_FLAGS_EDITABLE},
	  {LCD_MENU_ID_SpeedLine,                 2,   4,   LCD_MENU_ID_Joystick,         LCD_MENU_ID_NONE,                 NULL,           SpeedLineChangeHandler,       LCDMENU_MENU_FLAGS_EDITABLE},
    {LCD_MENU_ID_LCD,                         0,   2,   LCD_MENU_ID_NONE,         LCD_MENU_ID_Smily,	            "Display",      NULL,                         LCDMENU_MENU_FLAGS_NONE},
	  {LCD_MENU_ID_Smily,               	  3,   1,   LCD_MENU_ID_LCD,         LCD_MENU_ID_NONE,                 "Smily",           SmilyMenuHandler,           LCDMENU_MENU_FLAGS_NONE},
	  {LCD_MENU_ID_MittelFinger,              3,   2,   LCD_MENU_ID_LCD,         LCD_MENU_ID_NONE,                 "Mittel Finger",           MittelFingerMenuHandler,           LCDMENU_MENU_FLAGS_NONE},
};

uint8_t LCD_HandleRemoteRxMessage(RAPP_MSG_Type type, uint8_t size, uint8_t *data, RNWK_ShortAddrType srcAddr, bool *handled, RPHY_PacketDesc *packet) {
  (void)size;
  (void)packet;
  switch(type) {
     default:
      break;
  } /* switch */
  return ERR_OK;
}
#endif /* PL_CONFIG_HAS_LCD_MENU */

void DrawSmily(void) {
	GDisp1_Clear();
    GDisp1_UpdateFull();
	smily.width = 84;
	smily.height = 48;
	smily.size = 4032;
	smily.name = "Smily";
	smily.pixmap = pixelSmily;
	GDisp1_DrawMonoBitmap(0,0,&smily,GDisp1_COLOR_BLACK,GDisp1_COLOR_WHITE);
	GDisp1_UpdateFull();
	vTaskDelay(pdMS_TO_TICKS(1500));
}

void DrawMittelfinger(void) {
	GDisp1_Clear();
    GDisp1_UpdateFull();
	smily.width = 84;
	smily.height = 48;
	smily.size = 4032;
	smily.name = "Smily";
	smily.pixmap = pixelMittelfinger;
	GDisp1_DrawMonoBitmap(0,0,&smily,GDisp1_COLOR_BLACK,GDisp1_COLOR_WHITE);
	GDisp1_UpdateFull();
	vTaskDelay(pdMS_TO_TICKS(1500));
}

static void DrawLines(void) {

  int i;
  GDisp1_PixelDim x, y, w, h;

  GDisp1_Clear();
  GDisp1_UpdateFull();

  GDisp1_DrawBox(0, 0, 10, 10, 1, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  vTaskDelay(pdMS_TO_TICKS(500));

  GDisp1_DrawBox(GDisp1_GetWidth()-10, 0, 10, 10, 1, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  vTaskDelay(pdMS_TO_TICKS(500));

  GDisp1_DrawLine(0, 0, GDisp1_GetWidth(), GDisp1_GetHeight(), GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  vTaskDelay(pdMS_TO_TICKS(500));
  GDisp1_DrawLine(0, GDisp1_GetHeight(), GDisp1_GetWidth(), 0, GDisp1_COLOR_BLACK);
  GDisp1_UpdateFull();
  vTaskDelay(pdMS_TO_TICKS(500));
  for(i=0;i<10;i++) {
    GDisp1_DrawCircle(GDisp1_GetWidth()/2, GDisp1_GetHeight()/2, 5+i*2, GDisp1_COLOR_BLACK);
    GDisp1_UpdateFull();
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}

static void DrawFont(void) {
  FDisp1_PixelDim x, y;

  GDisp1_Clear();
  GDisp1_UpdateFull();
  x = 0;
  y = 10;
  FDisp1_WriteString("Hello World!", GDisp1_COLOR_BLACK, &x, &y, GFONT1_GetFont());
  GDisp1_UpdateFull();
  vTaskDelay(pdMS_TO_TICKS(500));
  x = 0;
  y += GFONT1_GetBoxHeight();
  FDisp1_WriteString("with Fonts!", GDisp1_COLOR_BLACK, &x, &y, GFONT1_GetFont());
  GDisp1_UpdateFull();
  WAIT1_Waitms(1000);
}

static void DrawText(void) {
  GDisp1_Clear();
  GDisp1_UpdateFull();
  PDC1_WriteLineStr(1, "hello");
  vTaskDelay(pdMS_TO_TICKS(200));
  PDC1_WriteLineStr(2, "world");
  vTaskDelay(pdMS_TO_TICKS(200));
  PDC1_WriteLineStr(3, "out");
  vTaskDelay(pdMS_TO_TICKS(200));
  PDC1_WriteLineStr(4, "there");
  vTaskDelay(pdMS_TO_TICKS(200));
  PDC1_WriteLineStr(5, "!!!!!");
  vTaskDelay(pdMS_TO_TICKS(200));
}

static void ShowTextOnLCD(unsigned char *text) {
  FDisp1_PixelDim x, y;

  GDisp1_Clear();
  x = 0;
  y = 10;
  FDisp1_WriteString(text, GDisp1_COLOR_BLACK, &x, &y, GFONT1_GetFont());
  GDisp1_UpdateFull();
}

static void LCD_Task(void *param) {
  (void)param; /* not used */
#if 1
  ShowTextOnLCD("Press a key!");
  //DrawText();
  /* \todo extend */
  //DrawFont();
  //DrawLines();

  //GDisp1_Clear();
  //GDisp1_UpdateFull();
  //GDisp1_SetPixel(10,10);
  //GDisp1_UpdateFull();

  DrawSmily();
  vTaskDelay(pdMS_TO_TICKS(500));
  //DrawMittelfinger();
  //DrawCircles(); MANUEL
#endif
#if PL_CONFIG_HAS_LCD_MENU
  LCDMenu_InitMenu(menus, sizeof(menus)/sizeof(menus[0]), 1);
  LCDMenu_OnEvent(LCDMENU_EVENT_DRAW, NULL);
#endif
  for(;;) {
    if (LedBackLightisOn) {
      LCD_LED_On(); /* LCD backlight on */
    } else {
      LCD_LED_Off(); /* LCD backlight off */
    }
#if PL_CONFIG_HAS_LCD_MENU
    if (requestLCDUpdate) {
      requestLCDUpdate = FALSE;
      LCDMenu_OnEvent(LCDMENU_EVENT_DRAW, NULL);
    }
#if 0 /*! \todo Change this to for your own needs, or use direct task notification */
    if (EVNT_EventIsSetAutoClear(EVNT_SW2_PRESSED)) { /* left *///EVNT_LCD_BTN_LEFT
      LCDMenu_OnEvent(LCDMENU_EVENT_LEFT, NULL);
//      ShowTextOnLCD("left");
    }
    if (EVNT_EventIsSetAutoClear(EVNT_SW1_PRESSED)) { /* right */ //EVNT_LCD_BTN_RIGHT
      LCDMenu_OnEvent(LCDMENU_EVENT_RIGHT, NULL);
//      ShowTextOnLCD("right");
    }
    if (EVNT_EventIsSetAutoClear(EVNT_SW5_PRESSED)) { /* up */  //EVNT_LCD_BTN_UP
      LCDMenu_OnEvent(LCDMENU_EVENT_UP, NULL);
//      ShowTextOnLCD("up");
    }
    if (EVNT_EventIsSetAutoClear(EVNT_SW3_PRESSED)) { /* down */  //EVNT_LCD_BTN_DOWN
      LCDMenu_OnEvent(LCDMENU_EVENT_DOWN, NULL);
//      ShowTextOnLCD("down");
    }
    if (EVNT_EventIsSetAutoClear(EVNT_SW4_PRESSED)) { /* center */ //EVNT_LCD_BTN_CENTER
      LCDMenu_OnEvent(LCDMENU_EVENT_ENTER, NULL);
//      ShowTextOnLCD("center");
    }
    if (EVNT_EventIsSetAutoClear(EVNT_SW7_PRESSED)) { /* side up */ //EVNT_LCD_SIDE_BTN_UP
      LCDMenu_OnEvent(LCDMENU_EVENT_UP, NULL);
//      ShowTextOnLCD("side up");
    }
    if (EVNT_EventIsSetAutoClear(EVNT_SW6_PRESSED)) { /* side down */ //EVNT_LCD_SIDE_BTN_DOWN
      LCDMenu_OnEvent(LCDMENU_EVENT_DOWN, NULL);
//      ShowTextOnLCD("side down");
    }
#endif
#endif /* PL_CONFIG_HAS_LCD_MENU */
    vTaskDelay(pdMS_TO_TICKS(20));
  }
}
void LCD_eventHandlerSwitch(EVNT_Handle event){
	switch(event) {
	#if PL_CONFIG_HAS_KEYS
	  #if PL_CONFIG_NOF_KEYS>=1
	  case EVNT_SW1_PRESSED:
		  /* right */ //EVNT_LCD_BTN_RIGHT
		  if(!JoystickIsOn){
		        LCDMenu_OnEvent(LCDMENU_EVENT_RIGHT, NULL);
		  }
		  //      ShowTextOnLCD("right");
	    break;
	  case EVNT_SW1_LPRESSED:
	  		  /* right */ //EVNT_LCD_BTN_RIGHT
	  		  //if(!JoystickIsOn){
	  		  //      LCDMenu_OnEvent(LCDMENU_EVENT_RIGHT, NULL);
	  		  //}
	  		  //      ShowTextOnLCD("right");
	  	    break;
	  #endif
	#if PL_LOCAL_CONFIG_NOF_KEYS>1
	  case EVNT_SW2_PRESSED:
		  /* left *///EVNT_LCD_BTN_LEFT
		  if(!JoystickIsOn){
		        LCDMenu_OnEvent(LCDMENU_EVENT_LEFT, NULL);
		  }
		  //      ShowTextOnLCD("left");
		  break;
	#endif
	#if PL_LOCAL_CONFIG_NOF_KEYS>2
	  case EVNT_SW3_PRESSED:
		  /* down */  //EVNT_LCD_BTN_DOWN
		  if(!JoystickIsOn){
		        LCDMenu_OnEvent(LCDMENU_EVENT_DOWN, NULL);
		  }else{
			  //Button_Pressed('B'); //MANUEL THOMAS
			  Button_Pressed('D'); //Slower
		  }
		  //      ShowTextOnLCD("down");
		  break;
	#endif
	#if PL_LOCAL_CONFIG_NOF_KEYS>3
	  case EVNT_SW4_PRESSED:
		  /* center */ //EVNT_LCD_BTN_CENTER
		  if(!JoystickIsOn){
		       LCDMenu_OnEvent(LCDMENU_EVENT_ENTER, NULL);
		  }else{
			  Button_Pressed('A'); //Begin line following
		  }
		 //      ShowTextOnLCD("center");
		  break;
	  case EVNT_SW4_LPRESSED:
	  		  /* center */ //EVNT_LCD_BTN_CENTER
	  		     LCDMenu_OnEvent(LCDMENU_EVENT_ENTER, NULL);
	  		 //      ShowTextOnLCD("center");
	  		  break;
	#endif
	#if PL_LOCAL_CONFIG_NOF_KEYS>4
	  case EVNT_SW5_PRESSED:
		  /* up */  //EVNT_LCD_BTN_UP
		  if(!JoystickIsOn){
		        LCDMenu_OnEvent(LCDMENU_EVENT_UP, NULL);
		  }else{
			  Button_Pressed('B'); //Faster
		  }

		  //      ShowTextOnLCD("up");
		  break;
	#endif
	#if PL_LOCAL_CONFIG_NOF_KEYS>5
	  case EVNT_SW6_PRESSED:
		  /* side down */ //EVNT_LCD_SIDE_BTN_DOWN
		  if(!JoystickIsOn){
		        LCDMenu_OnEvent(LCDMENU_EVENT_DOWN, NULL);
		  }else{

		  }
		  //      ShowTextOnLCD("side down");
		  break;
	#endif
	#if PL_LOCAL_CONFIG_NOF_KEYS>6
	  case EVNT_SW7_PRESSED:
		  /* side up */ //EVNT_LCD_SIDE_BTN_UP
		  if(!JoystickIsOn){
		        LCDMenu_OnEvent(LCDMENU_EVENT_UP, NULL);
		  }
		  //      ShowTextOnLCD("side up");
		  break;
	#endif

	#endif /* PL_CONFIG_HAS_KEYS */

	    /* \todo extend handler as needed */
	   } /* switch */
}



void LCD_Deinit(void) {
#if PL_CONFIG_HAS_LCD_MENU
  LCDMenu_Deinit();
#endif
}

void LCD_Init(void) {
  LedBackLightisOn =  TRUE;
  if (xTaskCreate(LCD_Task, "LCD", configMINIMAL_STACK_SIZE+100, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {//&LCDTaskHandle) != pdPASS) {
    for(;;){} /* error! probably out of memory */ //bigger stack old 30
  }
#if PL_CONFIG_HAS_LCD_MENU
  LCDMenu_Init();
#endif
}
#endif /* PL_CONFIG_HAS_LCD */
