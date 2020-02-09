/*
 * joypad.c
 *
 *  Created on: 2020. 2. 1.
 *      Author: Baram
 */




#include "joypad.h"
#include "button.h"



#define JOYPAD_ADC_MAX_COUNT     5
#define JOYPAD_DEAD_ZONE         200


static uint8_t  adc_ch_x = 0;
static uint8_t  adc_ch_y = 1;

static int32_t x_adc_value = 0;
static int32_t y_adc_value = 0;

static int32_t x_adc_offset = 0;
static int32_t y_adc_offset = 0;


static int32_t x_value = 0;
static int32_t y_value = 0;

static int32_t adc_data_x[JOYPAD_ADC_MAX_COUNT];
static int32_t adc_data_y[JOYPAD_ADC_MAX_COUNT];



static void joypadOffsetUpdate(void);


bool joypadInit(void)
{
  uint32_t i;

  for (i=0; i<JOYPAD_ADC_MAX_COUNT; i++)
  {
    adc_data_x[i] = 0;
    adc_data_y[i] = 0;
  }

  joypadOffsetUpdate();

  return true;
}

int32_t joypadGetAdc(uint8_t ch)
{
  int32_t ret = 0;
  float x, y;

  buttonGetPad(&x, &y);

  if (ch == 0) 
  {
    ret = constrain(x*2000, -2000, 2000);
  }
  else
  {
    ret = constrain(y*2000, -2000, 2000);
  }

  ret = 0;
}

void joypadOffsetUpdate(void)
{
  uint32_t i;
  int32_t sum;


  for (i=0; i<JOYPAD_ADC_MAX_COUNT; i++)
  {    
    adc_data_x[i] = joypadGetAdc(adc_ch_x);
    adc_data_y[i] = joypadGetAdc(adc_ch_y);
    delay(10);
  }


  sum = 0;
  for (i=0; i<JOYPAD_ADC_MAX_COUNT; i++)
  {
    sum += adc_data_x[i];
  }
  x_adc_value = sum / JOYPAD_ADC_MAX_COUNT;

  sum = 0;
  for (i=0; i<JOYPAD_ADC_MAX_COUNT; i++)
  {
    sum += adc_data_y[i];
  }
  y_adc_value = sum / JOYPAD_ADC_MAX_COUNT;


  x_adc_offset = x_adc_value;
  y_adc_offset = y_adc_value;
}


void joypadUpdate(void)
{
  int32_t value;


  x_adc_value = joypadGetAdc(adc_ch_x);
  y_adc_value = joypadGetAdc(adc_ch_y);

  value = -constrain(x_adc_value-x_adc_offset, -2000, 2000);
  if (value > 0)
  {
    value = constrain(value, JOYPAD_DEAD_ZONE, 2000);
    x_value = map(value, JOYPAD_DEAD_ZONE, 2000, 0, 100);
  }
  else if (value < 0)
  {
    value = constrain(value, -2000, -JOYPAD_DEAD_ZONE);
    x_value = map(value, -2000, -JOYPAD_DEAD_ZONE, -100, 0);
  }
  else
  {
    x_value = 0;
  } 


  value = -constrain(y_adc_value-y_adc_offset, -2000, 2000);
  if (value > 0)
  {
    value = constrain(value, JOYPAD_DEAD_ZONE, 2000);
    y_value = map(value, JOYPAD_DEAD_ZONE, 2000, 0, 100);
  }
  else if (value < 0)
  {
    value = constrain(value, -2000, -JOYPAD_DEAD_ZONE);
    y_value = map(value, -2000, -JOYPAD_DEAD_ZONE, -100, 0);
  }
  else
  {
    y_value = 0;
  } 
}

int32_t joypadGetX(void)
{
  joypadUpdate();

  return x_value;
}

int32_t joypadGetY(void)
{
  joypadUpdate();

  return y_value;
}



bool joypadGetPressedButton(uint8_t ch)
{
  bool ret = false;

  joypadUpdate();

  switch(ch)
  {
    case 0:
      if (x_value > 50) ret = true;
      break;

    case 1:
      if (x_value < -50) ret = true;
      break;

    case 2:
      if (y_value > 50) ret = true;
      break;

    case 3:
      if (y_value < -50) ret = true;
      break;
  }


  return ret;
}
