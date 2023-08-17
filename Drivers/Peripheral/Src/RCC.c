#include "RCC.h"

void system_clock(void)
{
  // Reset PLL register
  RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLP | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLM);
  // give value of pll(p,n and m)
  RCC->PLLCFGR |= (PLL_P << 16 | PLL_N << 8 | PLL_M << 0);
  // enable HSE clock
  RCC->CR |= RCC_CR_HSEON;
  // wait to HSE clock to ready
  while (!(RCC->CR & RCC_CR_HSERDY))
    ;
  // Select source HSE for main PLL
  RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC;
  // Enable main PLL
  RCC->CR |= RCC_CR_PLLON;
  // wait to main Pll to ready
  while (!(RCC->CR & RCC_CR_PLLRDY))
    ;
  // enable prefetch
  FLASH->ACR |= FLASH_ACR_PRFTEN;
  // clear register Latency
  FLASH->ACR &= ~(FLASH_ACR_LATENCY);
  // latency 5 wait-state
  FLASH->ACR |= FLASH_ACR_LATENCY_5WS;
  // Select system clock: PLL_P
  RCC->CFGR &= ~(RCC_CFGR_SW);
  RCC->CFGR |= RCC_CFGR_SW_PLL;
  while (!(RCC->CFGR & RCC_CFGR_SWS_PLL))
    ;
  // AHB = 1
  RCC->CFGR &= ~(RCC_CFGR_HPRE);
  // APB1 = 4
  RCC->CFGR &= ~(RCC_CFGR_PPRE1);
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
  // APB2 = 2
  RCC->CFGR &= ~(RCC_CFGR_PPRE2);
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
}