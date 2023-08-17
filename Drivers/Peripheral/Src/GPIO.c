#include "GPIO.h"

void gpio_led_init(void)
{
  // Enable AHB1 clock for GPIOA
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  // PA5 is Output
  GPIOA->MODER &= ~(GPIO_MODER_MODE5);
  GPIOA->MODER |= GPIO_MODER_MODE5_0;
  // PA5 push-pull (high-low)
  GPIOA->OTYPER &= ~(GPIO_OTYPER_OT5);
  // speed of state change: low-speed
  GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED5);
  // PA5 no-pull
  GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPD5);
}

void gpio_led_write(e_state state)
{
  if (state == high)
    GPIOA->ODR |= GPIO_ODR_OD5;
  else
    GPIOA->ODR &= ~(GPIO_ODR_OD5);
}

void gpio_led_toggle(void)
{
  GPIOA->ODR ^= GPIO_ODR_OD5;
}

void gpio_btn_init(void)
{
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
  GPIOC->MODER &= ~(GPIO_MODER_MODE13);
  GPIOC->OTYPER &= ~(GPIO_OTYPER_OT13);
  // speed of state change: low-speed
  GPIOC->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED13);
  // PA5 no-pull
  GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPD13);
}

e_state gpio_btn_read(void)
{
  return (GPIOC->IDR & GPIO_IDR_ID13) ? high : low;
}