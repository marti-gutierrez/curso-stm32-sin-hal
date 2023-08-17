#include "main.h"
#include "RCC.h"
#include "GPIO.h"

int main(void)
{
  system_clock();
  gpio_led_init();
  gpio_btn_init();
  while (1)
  {
    gpio_led_write(gpio_btn_read());
    for (uint32_t i = 0; i < 1000000; i++)
      ;
  }
  return 0;
}
