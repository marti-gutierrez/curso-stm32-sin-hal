#include "USART.h"
#include <errno.h>

int _write(int file, char *ptr, int len);

int _write(int file, char *ptr, int len)
{
  if (file != 1)
  {
    errno = EBADF;
    return -1;
    /* i > 0 false
       i < 0 error
    */
  }
  uint8_t i;
  for (i = 0; i < len; i++)
    USART_tx(ptr[i]);
  return i;
}