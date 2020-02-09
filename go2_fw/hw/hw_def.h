#ifndef SRC_HW_HW_DEF_H_
#define SRC_HW_HW_DEF_H_


#include "def.h"


extern uint32_t millis(void);
extern uint32_t micros(void);
extern void delay(uint32_t ms);



#define _USE_HW_DELAY
#define _USE_HW_MILLIS
#define _USE_HW_MICROS



#define _USE_HW_LCD
#define      HW_LCD_WIDTH           480
#define      HW_LCD_HEIGHT          320

#define _USE_HW_BUTTON
#define      HW_BUTTON_MAX_CH       16

#define _USE_HW_ADC
#define      HW_ADC_MAX_CH          2

#define _USE_HW_JOYPAD

#define _USE_HW_SPEAKER



#define _DEF_HW_BTN_LEFT            0
#define _DEF_HW_BTN_RIGHT           1
#define _DEF_HW_BTN_UP              2
#define _DEF_HW_BTN_DOWN            3

#define _DEF_HW_BTN_A               4
#define _DEF_HW_BTN_B               5
#define _DEF_HW_BTN_X               6
#define _DEF_HW_BTN_Y               7

#define _DEF_HW_BTN_L1              8
#define _DEF_HW_BTN_R1              9

#define _DEF_HW_BTN_MENU            10
#define _DEF_HW_BTN_HOME            11

#define _DEF_HW_BTN_SELECT          12
#define _DEF_HW_BTN_START           13

#define _DEF_HW_BTN_F5              14
#define _DEF_HW_BTN_F6              15

#define _DEF_HW_BTN_F1              10
#define _DEF_HW_BTN_F2              11
#define _DEF_HW_BTN_F3              12
#define _DEF_HW_BTN_F4              13



#endif /* SRC_HW_HW_DEF_H_ */
