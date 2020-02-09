/*
 * speaker.c
 *
 *  Created on: 2020. 2. 1.
 *      Author: Baram
 */




#include "hw/include/speaker.h"


static uint8_t volume = 100;


bool speakerInit(void)
{

  speakerDisable();

  return true;
}

void speakerEnable(void)
{
}

void speakerDisable(void)
{
}

void speakerSetVolume(uint8_t volume_data)
{
  if (volume != volume_data)
  {
    volume = volume_data;
  }
}

uint8_t speakerGetVolume(void)
{
  return volume;
}


void speakerStart(uint32_t hz)
{
}

void speakerStop(void)
{
}

void speakerReStart(void)
{
}

uint32_t speakerAvailable(void)
{
  return 0;
}

uint32_t speakerGetBufLength(void)
{
  return 0;
}

void speakerPutch(uint8_t data)
{
  
}

void speakerWrite(uint8_t *p_data, uint32_t length)
{
  uint32_t i;


  for (i=0; i<length; i++)
  {
    speakerPutch(p_data[i]);
  }
}
