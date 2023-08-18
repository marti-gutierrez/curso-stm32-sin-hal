#include "main.h"
#include "RCC.h"
#include "GPIO.h"
#include "EXT_IT.h"
#include "SysTick.h"

s_delay time;

int main(void)
{
  system_clock();
  SysTick_init(180000);
  gpio_led_init();
  gpio_btn_init();
  init_EXT_IT();
  gpio_led_write(low);
  delay_ms_NB(&time, 200);
  while (1)
  {
    if (delay_read(&time))
    {
      gpio_led_toggle();
    }
  }
  return 0;
}

void EXTI15_10_IRQHandler(void)
{
  NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
  EXTI->PR |= EXTI_PR_PR13;
  gpio_led_toggle();
}
