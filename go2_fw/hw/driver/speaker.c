/*
 * speaker.c
 *
 *  Created on: 2020. 2. 1.
 *      Author: Baram
 */




#include "speaker.h"
#include "audio.h"

#include <pthread.h>
#include <semaphore.h>


static uint8_t volume = 100;
static go2_audio_t* audio = NULL;

static pthread_t thread_id;
static sem_t semaphore;
static bool terminating = false;
static uint16_t *submit_data;
static uint32_t submit_frame_count;
static bool is_requested = false;

void *speakerThread(void *arg)
{
  while(!terminating)
  {
    sem_wait(&semaphore);
    uint32_t pre_time;

    pre_time = micros();
    go2_audio_submit(audio, submit_data, submit_frame_count);
    //logPrintf("%d us\n", micros()-pre_time);
    is_requested = false;
  }  
  return NULL;
}



bool speakerInit(void)
{

  speakerDisable();


  if (sem_init(&semaphore, 0, 0) != 0)
  {
    logPrintf("could not create sem_init thread\n");
    return false;
  }
  if(pthread_create(&thread_id, NULL, speakerThread, NULL) < 0)
  {
    logPrintf("could not create speakerThread thread\n");
    return false;  
  }  

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
  if (audio != NULL)
  {
    go2_audio_destroy(audio);
  }
  audio = go2_audio_create(hz);

  logPrintf("volume : %d \n", go2_audio_volume_get(audio));  
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

void speakerSubmit(uint16_t *p_data, uint32_t frame_count)
{
  if (audio != NULL)
  {
    submit_data = p_data;
    submit_frame_count = frame_count;

    while(is_requested)
    {
      delay(1);
    }    

    is_requested = true;
    sem_post(&semaphore);    
  }
}


