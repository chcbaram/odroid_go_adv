/*
 * delay.c
 *
 *  Created on: 2020. 1. 21.
 *      Author: Baram
 */




#include "delay.h"
#include "millis.h"



bool delayInit(void)
{
  return true;
}

void delay(uint32_t ms)
{
  uint32_t pre_time;

  pre_time = millis();
  while(millis()-pre_time >= ms);
}

void delayNs(uint32_t ns)
{

}

void delayUs(uint32_t us)
{
}

void delayMs(uint32_t ms)
{
  delay(ms);
}
