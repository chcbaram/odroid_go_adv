#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_


#include "def.h"


extern uint32_t millis(void);
extern void delay(uint32_t ms);



#define _USE_HW_DELAY
#define _USE_HW_MILLIS




#define _USE_HW_LCD
#define      HW_LCD_WIDTH           480
#define      HW_LCD_HEIGHT          320

#define _USE_HW_BUTTON
#define      HW_BUTTON_MAX_CH       10

#define _USE_HW_ADC
#define      HW_ADC_MAX_CH          2

#define _USE_HW_JOYPAD

#define _USE_HW_SPEAKER



#define _DEF_HW_BTN_A               0
#define _DEF_HW_BTN_B               1
#define _DEF_HW_BTN_SELECT          2
#define _DEF_HW_BTN_START           3
#define _DEF_HW_BTN_MENU            4
#define _DEF_HW_BTN_HOME            5
#define _DEF_HW_BTN_LEFT            6
#define _DEF_HW_BTN_RIGHT           7
#define _DEF_HW_BTN_UP              8
#define _DEF_HW_BTN_DOWN            9





#endif /* SRC_HW_HW_DEF_H_ */
