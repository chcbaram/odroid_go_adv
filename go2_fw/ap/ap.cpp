/*
 * ap.cpp
 *
 *  Created on: 2020. 1. 21.
 *      Author: Baram
 */




#include "ap.h"


extern "C"
{
void gnuboyMain (void);
}



void apInit(void)
{
  hwInit();

  gnuboyMain();
}


void apMain(void)
{
  uint32_t pre_time;
  uint32_t pre_time2;
  uint16_t x = 0;
  uint16_t y = 0;

  while(1)
  {
    if (millis()-pre_time >= 500)
    {
      pre_time = millis();
      //logPrintf("X : %d\n", (int)joypadGetX());
      //logPrintf("Y : %d\n", (int)joypadGetY());

      for (int i=0; i<BUTTON_MAX_CH; i++)
      {
        logPrintf("%d", buttonGetPressed(i));
      }
      logPrintf("\n");    
    }

    if (lcdDrawAvailable() > 0)
    {
      lcdClearBuffer(black);

      lcdPrintf(150, 0, white, "오드로이드 고 어드벤스");

      lcdPrintf(0,  0, white, "%d ms", lcdGetFpsTime());
      lcdPrintf(0, 16, white, "%d fps", lcdGetFps());

      lcdDrawFillRect(x, 32, 30, 30, red);
      lcdDrawFillRect(lcdGetWidth()-x, 62, 30, 30, green);
      lcdDrawFillRect(x + 30, 92, 100, 100, blue);

      x += 4;

      x %= lcdGetWidth();
      y %= lcdGetHeight();

      lcdRequestDraw();
    }
  }
}




