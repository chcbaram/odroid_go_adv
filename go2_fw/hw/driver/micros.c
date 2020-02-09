#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#include <sys/time.h>
#include <sys/ioctl.h>

#include "micros.h"


bool microsInit(void)
{
  return true;
}


uint32_t micros(void)
{
  double ret;
  uint64_t value;


  struct timespec tv;
	clock_gettime( CLOCK_REALTIME, &tv);

  if (tv.tv_nsec < 0)
  {
    tv.tv_nsec = -tv.tv_nsec;
  }
  ret = ((double)tv.tv_sec*1000000.0 + (double)tv.tv_nsec*0.001);

  value = (uint64_t)ret;

  return (uint32_t)value;
}
