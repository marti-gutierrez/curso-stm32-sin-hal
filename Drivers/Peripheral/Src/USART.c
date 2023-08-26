#include "USART.h"
#include "SysTick.h"

s_delay time_uart;

/*The Nucleo Board use of USART2 (PA2->USART2_TX/PA3->USART2_RX)*/

static void USART_gpio(void)
{
  // 1.enable bus clock AHB1 for GPIOA
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
  // 2.GPIOA port mode: alternate function
  GPIOA->MODER &= ~(GPIO_MODER_MODER3 | GPIO_MODER_MODER2); // clear moder register-2 and 3
  GPIOA->MODER |= (GPIO_MODER_MODER3_1 | GPIO_MODER_MODER2_1);
  // 3.GPIOA port output type: push pull
  GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_3 | GPIO_OTYPER_OT_2);
  // 4.GPIOA speed: high speed
  GPIOA->OSPEEDR &= ~(GPIO_OSPEEDR_OSPEED3 | GPIO_OSPEEDR_OSPEED2);
  GPIOA->OSPEEDR |= (GPIO_OSPEEDR_OSPEED3 | GPIO_OSPEEDR_OSPEED2);
  // 5.GPIOA pull-up/pull-down: no pull
  GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR3 | GPIO_PUPDR_PUPDR2);
  // 6.GPIOA alternate function: AF7
  GPIOA->AFR[0] &= ~(GPIO_AFRL_AFRL3 | GPIO_AFRL_AFRL2);
  GPIOA->AFR[0] |= (GPIO_AFRL_AFRL3_0 | GPIO_AFRL_AFRL3_1 | GPIO_AFRL_AFRL3_2);
  GPIOA->AFR[0] |= (GPIO_AFRL_AFRL2_0 | GPIO_AFRL_AFRL2_1 | GPIO_AFRL_AFRL2_2);
}

void USART_init(uint32_t BAUD)
{
  USART_gpio();
  // enable bus clock APB1 for USART2
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
  // <-- USART Register Configuration -->
  // 1.USART baud rate
  USART2->BRR = (2 * CLOCK_USART2 + BAUD) / (2 * BAUD);
  // 2.USART word length: 8 bits
  USART2->CR1 &= ~(USART_CR1_M);
  // 3.USART parity control: none
  USART2->CR1 &= ~(USART_CR1_PCE);
  USART2->CR1 &= ~(USART_CR1_PS); // even parity
  // 4.disable RTS and CTS flow control
  USART2->CR3 &= ~(USART_CR3_CTSE | USART_CR3_RTSE);
  // 5. stop bit: 1 bit
  USART2->CR2 &= ~(USART_CR2_STOP);
  // 6. select full-duplex mode
  USART2->CR3 &= ~(USART_CR3_HDSEL);
  // 7.enable TX and RX
  USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE);
  // 8.enable USART
  USART2->CR1 |= USART_CR1_UE;
}

void USART_tx(char data)
{
  while (!(USART2->SR & USART_SR_TC)) // wait until transmit is complete
    ;
  USART2->DR = data & USART_DR_DR;
}

char USART_rx(void)
{
  while (!(USART2->SR & USART_SR_RXNE))
    ; // wait until receive buffer is not empty
  return USART2->DR & USART_DR_DR;
}

void USART_tx_str(char *str)
{
  while (*str != '\0')
  {
    USART_tx(*str);
    str++;
  }
}

bool USART_rx_str(char *str, uint32_t len, uint32_t timeout)
{
  delay_ms_NB(&time_uart, timeout);
  while (len > 0)
  {
    if (USART2->SR & USART_SR_RXNE)
    {
      *str++ = USART2->DR & USART_DR_DR;
      len--;
    }
    if (delay_read(&time_uart))
      return false;
  }
  return true;
}
