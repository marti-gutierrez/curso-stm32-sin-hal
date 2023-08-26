#include "main.h"
#include "RCC.h"
#include "USART.h"
#include "SysTick.h"

#define len_data 10

char data[len_data];

int main(void)
{
  system_clock();
  SysTick_init(180000);
  USART_init(115200);
  printf("Hi Jorge\n\r");
  while (1)
  {
    if (USART_rx_str(data, len_data, 10))
      printf("Data: %s\n\r", data);
  }
  return 0;
}
