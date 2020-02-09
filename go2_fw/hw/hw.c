#include "hw.h"




void hwInit(void)
{

  //delayInit();
  millisInit();

  //ledInit();
  //adcInit();  
  buttonInit();
  joypadInit();




  logPrintf("Start...\r\n");


  //speakerInit();
  lcdInit();
}

void hwDeInit(void)
{
  buttonDeInit();
}