#ifndef SRC_HW_HW_H_
#define SRC_HW_HW_H_


#ifdef __cplusplus
extern "C" {
#endif


#include "hw_def.h"

#include "delay.h"
#include "micros.h"
#include "millis.h"
#include "lcd.h"
#include "button.h"
#include "joypad.h"
#include "speaker.h"


void hwInit(void);
void hwDeInit(void);

#ifdef __cplusplus
}
#endif


#endif /* SRC_HW_HW_H_ */
