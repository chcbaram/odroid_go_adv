#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#include <sys/time.h>
#include <sys/ioctl.h>

#include "millis.h"


bool millisInit(void)
{
  return true;
}


uint32_t millis(void)
{
  double ret;
  struct timespec tv;
	clock_gettime( CLOCK_MONOTONIC, &tv);


  ret = ((double)tv.tv_sec*1000.0 + (double)tv.tv_nsec*0.001*0.001);

  return (uint32_t)ret;
}
