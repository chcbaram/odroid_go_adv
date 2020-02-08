#include "hw.h"




void hwInit(void)
{

  //delayInit();
  millisInit();

  //ledInit();
  //adcInit();
  //joypadInit();
  //buttonInit();




  logPrintf("Start...\r\n");


  //speakerInit();
  lcdInit();
}
