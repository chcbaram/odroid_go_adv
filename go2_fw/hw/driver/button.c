/*
 * button.c
 *
 *  Created on: 2020. 2. 1.
 *      Author: Baram
 */



#include <pthread.h>

#include "button.h"
#include "joypad.h"
#include "input.h"


typedef struct
{
} button_tbl_t;




typedef struct
{
  bool        pressed;
  bool        pressed_event;
  uint16_t    pressed_cnt;
  uint32_t    pressed_start_time;
  uint32_t    pressed_end_time;

  bool        released;
  bool        released_event;
  uint32_t    released_start_time;
  uint32_t    released_end_time;

} button_t;

static bool is_init = false;
static button_t button_tbl[BUTTON_MAX_CH];

static go2_input_t* go2input = NULL;
static go2_gamepad_state_t button_state;
static pthread_mutex_t button_mutex;
static pthread_t thread_id;
static bool terminating = false;


#ifdef _USE_HW_CMDIF
void buttonCmdifInit(void);
void buttonCmdif(void);
#endif

static bool is_enable = true;
static bool buttonGetPin(uint8_t ch);


void button_isr(void *arg)
{
  uint8_t i;


  for (i=0; i<BUTTON_MAX_CH; i++)
  {

    if (buttonGetPin(i))
    {
      if (button_tbl[i].pressed == false)
      {
        button_tbl[i].pressed_event = true;
        button_tbl[i].pressed_start_time = millis();
      }

      button_tbl[i].pressed = true;
      button_tbl[i].pressed_cnt++;

      button_tbl[i].pressed_end_time = millis();

      button_tbl[i].released = false;
    }
    else
    {
      if (button_tbl[i].pressed == true)
      {
        button_tbl[i].released_event = true;
        button_tbl[i].released_start_time = millis();
      }

      button_tbl[i].pressed  = false;
      button_tbl[i].released = true;

      button_tbl[i].released_end_time = millis();
    }
  }
}


static void* button_task(void* arg)
{
	while (!terminating)
	{
    pthread_mutex_lock(&button_mutex);
    go2_input_gamepad_read(go2input, &button_state);
    pthread_mutex_unlock(&button_mutex); 

    button_isr(NULL);
    sleep(0.001);
  }
  return NULL;
}



bool buttonInit(void)
{
  uint32_t i;


  for (i=0; i<BUTTON_MAX_CH; i++)
  {
    button_tbl[i].pressed_cnt    = 0;
    button_tbl[i].pressed        = 0;
    button_tbl[i].released       = 0;
    button_tbl[i].released_event = 0;
  }

#ifdef _USE_HW_CMDIF
  buttonCmdifInit();
#endif


  go2input = go2_input_create();

  if(pthread_create(&thread_id, NULL, button_task, NULL) < 0)
  {
    logPrintf("could not create button_task thread\n");
    return false;  
  }

  is_init = true;

  delay(10);
  return true;
}

bool buttonDeInit(void)
{

  if (go2input  != NULL)
  {
    go2_input_destroy(go2input);
  }
  return true;
}

void buttonResetTime(uint8_t ch)
{
  button_tbl[ch].pressed_start_time    = 0;
  button_tbl[ch].pressed_end_time      = 0;
  button_tbl[ch].released_start_time   = 0;
  button_tbl[ch].released_end_time     = 0;

  button_tbl[ch].pressed_event = false;
  button_tbl[ch].released_event = false;
}

bool buttonGetPin(uint8_t ch)
{
  bool ret = false;

  if (ch >= BUTTON_MAX_CH)
  {
    return false;
  }  


  if (ch == _DEF_HW_BTN_LEFT  && button_state.dpad.left) ret = true;
  if (ch == _DEF_HW_BTN_RIGHT && button_state.dpad.right) ret = true;
  if (ch == _DEF_HW_BTN_UP    && button_state.dpad.up) ret = true;
  if (ch == _DEF_HW_BTN_DOWN  && button_state.dpad.down) ret = true;

  if (ch == _DEF_HW_BTN_A && button_state.buttons.a) ret = true;
  if (ch == _DEF_HW_BTN_B && button_state.buttons.b) ret = true;
  if (ch == _DEF_HW_BTN_X && button_state.buttons.x) ret = true;
  if (ch == _DEF_HW_BTN_Y && button_state.buttons.y) ret = true;

  if (ch == _DEF_HW_BTN_L1 && button_state.buttons.top_left) ret = true;
  if (ch == _DEF_HW_BTN_R1 && button_state.buttons.top_right) ret = true;

  if (ch == _DEF_HW_BTN_MENU && button_state.buttons.f1) ret = true;
  if (ch == _DEF_HW_BTN_HOME && button_state.buttons.f2) ret = true;
  if (ch == _DEF_HW_BTN_SELECT && button_state.buttons.f3) ret = true;
  if (ch == _DEF_HW_BTN_START && button_state.buttons.f4) ret = true;

  if (ch == _DEF_HW_BTN_F5 && button_state.buttons.f5) ret = true;
  if (ch == _DEF_HW_BTN_F6 && button_state.buttons.f6) ret = true;

  if (ch == _DEF_HW_BTN_LEFT  && joypadGetPressedButton(0)) ret = true;
  if (ch == _DEF_HW_BTN_RIGHT && joypadGetPressedButton(1)) ret = true;
  if (ch == _DEF_HW_BTN_UP    && joypadGetPressedButton(2)) ret = true;
  if (ch == _DEF_HW_BTN_DOWN  && joypadGetPressedButton(3)) ret = true;

  return ret;
}

void buttonGetPad(float *p_x, float *p_y)
{
  pthread_mutex_lock(&button_mutex);
  *p_x = button_state.thumb.x;
  *p_y = button_state.thumb.y;
  pthread_mutex_unlock(&button_mutex);   
}

void buttonEnable(bool enable)
{
  is_enable = enable;
}

bool buttonGetPressed(uint8_t ch)
{
  if (ch >= BUTTON_MAX_CH || is_enable == false)
  {
    return false;
  }

  return button_tbl[ch].pressed;
}

bool buttonOsdGetPressed(uint8_t ch)
{
  if (ch >= BUTTON_MAX_CH)
  {
    return false;
  }

  return button_tbl[ch].pressed;
}

bool buttonGetPressedEvent(uint8_t ch)
{
  bool ret;


  if (ch >= BUTTON_MAX_CH || is_enable == false) return false;

  ret = button_tbl[ch].pressed_event;

  button_tbl[ch].pressed_event = 0;

  return ret;
}

uint32_t buttonGetPressedTime(uint8_t ch)
{
  volatile uint32_t ret;


  if (ch >= BUTTON_MAX_CH || is_enable == false) return 0;


  ret = button_tbl[ch].pressed_end_time - button_tbl[ch].pressed_start_time;

  return ret;
}


bool buttonGetReleased(uint8_t ch)
{
  bool ret;


  if (ch >= BUTTON_MAX_CH || is_enable == false) return false;

  ret = button_tbl[ch].released;

  return ret;
}

bool buttonGetReleasedEvent(uint8_t ch)
{
  bool ret;


  if (ch >= BUTTON_MAX_CH || is_enable == false) return false;

  ret = button_tbl[ch].released_event;

  button_tbl[ch].released_event = 0;

  return ret;
}

uint32_t buttonGetReleasedTime(uint8_t ch)
{
  volatile uint32_t ret;


  if (ch >= BUTTON_MAX_CH || is_enable == false) return 0;


  ret = button_tbl[ch].released_end_time - button_tbl[ch].released_start_time;

  return ret;
}



#ifdef _USE_HW_CMDIF
void buttonCmdifInit(void)
{
  cmdifAdd("button", buttonCmdif);
}

void buttonCmdif(void)
{
  bool ret = true;
  uint8_t ch;
  uint32_t i;


  if (cmdifGetParamCnt() == 1)
  {
    if(cmdifHasString("show", 0) == true)
    {
      while(cmdifRxAvailable() == 0)
      {
        for (i=0; i<BUTTON_MAX_CH; i++)
        {
          cmdifPrintf("%d", buttonGetPressed(i));
        }
        cmdifPrintf("\r");
        delay(50);
      }
    }
    else
    {
      ret = false;
    }
  }
  else if (cmdifGetParamCnt() == 2)
  {
    ch = (uint8_t)cmdifGetParam(1);

    if (ch > 0)
    {
      ch--;
    }

    if (cmdifHasString("time", 0) == true)
    {
      while(cmdifRxAvailable() == 0)
      {
        if(buttonGetPressed(ch))
        {
          cmdifPrintf("BUTTON%d, Time :  %d ms\n", ch+1, buttonGetPressedTime(ch));
        }
      }
    }
    else
    {
      ret = false;
    }
  }
  else
  {
    ret = false;
  }


  if (ret == false)
  {
    cmdifPrintf( "button [show/time] channel(1~%d) ...\n", BUTTON_MAX_CH);
  }
}
#endif
