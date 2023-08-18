#include "SysTick.h"

void SysTick_init(uint32_t systick_value)
{
  // Counter disable of SysTic
  SysTick->CTRL &= ~(SysTick_CTRL_ENABLE_Msk);
  // Load value
  SysTick->LOAD &= ~(SysTick_LOAD_RELOAD_Msk);
  SysTick->LOAD = systick_value - 1;
  NVIC_SetPriority(SysTick_IRQn, 0);
  // Clear current Value
  SysTick->VAL = 0;
  // Configure Systick: Source: processor clk,enable request, enable SysTick
  SysTick->CTRL |= (SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk);
  NVIC_EnableIRQ(SysTick_IRQn);
}

void SysTick_Handler(void)
{
  NVIC_ClearPendingIRQ(SysTick_IRQn);
  ms_inc_tick();
}

void ms_inc_tick(void)
{
  ms_tick++;
}

uint32_t get_ms_ticks(void)
{
  return ms_tick;
}

/// @brief delay for wait
/// @param time_ms time in miliseconds
void delay_ms(uint32_t time_ms)
{
  uint32_t start_time = get_ms_ticks();
  while ((get_ms_ticks() - start_time) < time_ms)
    ;
}
/// @brief delay for wait for systick
/// @param time_ms time in miliseconds
void delay_ms_NB(s_delay *delay, uint32_t time_ms)
{
  delay->duration = time_ms;
  delay->running = false;
}
bool delay_read(s_delay *delay)
{
  bool time_arrived = false;
  if (!delay->running)
  {
    delay->start_time = get_ms_ticks();
    delay->running = true;
  }
  if ((get_ms_ticks() - delay->start_time) >= delay->duration)
  {
    time_arrived = true;
    delay->running = false;
  }
  return time_arrived;
}