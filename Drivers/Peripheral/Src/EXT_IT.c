#include "EXT_IT.h"

void init_EXT_IT(void)
{
  // enable clock controller (APB2) for system config controller
  RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
  // clear EXTI13
  SYSCFG->EXTICR[3] &= ~(SYSCFG_EXTICR4_EXTI13_Msk);
  // select pin 13(EXTI13) Port-C = 0x0020;
  SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI13_PC;
  // line 13 no masked
  EXTI->IMR |= EXTI_IMR_IM13;
  // Event request from line 13
  EXTI->EMR |= EXTI_EMR_EM13;
  // Rising trigger disabled of line 13
  EXTI->RTSR &= ~(EXTI_RTSR_TR13);
  // Falling trigger enable of line 13
  EXTI->FTSR |= EXTI_FTSR_TR13;
  // configure priority
  NVIC_SetPriority(EXTI15_10_IRQn, 2);
  // enable priority
  NVIC_EnableIRQ(EXTI15_10_IRQn);
}