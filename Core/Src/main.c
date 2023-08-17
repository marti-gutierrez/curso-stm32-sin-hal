#include "main.h"
#include "RCC.h"
#include "GPIO.h"
#include "EXT_IT.h"

int main(void)
{
  system_clock();
  gpio_led_init();
  gpio_btn_init();
  init_EXT_IT();
  gpio_led_write(low);
  while (1)
  {
  }
  return 0;
}

void EXTI15_10_IRQHandler(void)
{
  NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
  EXTI->PR |= EXTI_PR_PR13;
  gpio_led_toggle();
}
