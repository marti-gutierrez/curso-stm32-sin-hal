#include "Timer_2.h"

/// @brief
/// @param r_autoreload load value for register ARR
void timer2_delay(uint32_t r_autoreload)
{
  // Enable clock for TIM2
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
  // counter as upcounter
  TIM2->CR1 &= ~(TIM_CR1_DIR);
  // one pulse mode: counter stop
  TIM2->CR1 |= TIM_CR1_OPM;
  // clear Master-Mode selection
  TIM2->CR2 &= ~(TIM_CR2_MMS);
  TIM2->PSC = 0;
  TIM2->ARR = r_autoreload - 1;
}