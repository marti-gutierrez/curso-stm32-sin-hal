#include "HD44780.h"

static void HD44780_gpio(void)
{
  // Enable GPIO-A/C clock
  RCC->AHB1ENR |= (RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN);
  // Configure GPIO-A/C pins Outputs
  GPIOC->MODER &= ~(GPIO_MODER_MODE12 | GPIO_MODER_MODE11 | GPIO_MODER_MODE10);
  GPIOC->MODER |= (GPIO_MODER_MODE12_0 | GPIO_MODER_MODE11_0 | GPIO_MODER_MODE10_0);
  GPIOA->MODER &= ~(GPIO_MODER_MODE4 | GPIO_MODER_MODE1 | GPIO_MODER_MODE0);
  GPIOA->MODER |= (GPIO_MODER_MODE4_0 | GPIO_MODER_MODE1_0 | GPIO_MODER_MODE0_0);
  // Configure GPIO-A/C pins Output mode push-pull
  GPIOC->OTYPER &= ~(GPIO_OTYPER_OT12 | GPIO_OTYPER_OT11 | GPIO_OTYPER_OT10);
  GPIOA->OTYPER &= ~(GPIO_OTYPER_OT4 | GPIO_OTYPER_OT1 | GPIO_OTYPER_OT0);
  // Output speed: Medium speed
  GPIOC->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR12 | GPIO_OSPEEDER_OSPEEDR11 | GPIO_OSPEEDER_OSPEEDR10);
  GPIOA->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR4 | GPIO_OSPEEDER_OSPEEDR1 | GPIO_OSPEEDER_OSPEEDR0);
  // Output PUPD: No pull-up, pull-down
  GPIOC->PUPDR &= ~(GPIO_PUPDR_PUPDR12 | GPIO_PUPDR_PUPDR11 | GPIO_PUPDR_PUPDR10);
  GPIOA->PUPDR &= ~(GPIO_PUPDR_PUPDR4 | GPIO_PUPDR_PUPDR1 | GPIO_PUPDR_PUPDR0);
}

static void trigger_enable(void)
{
  GPIOC->ODR |= GPIO_ODR_OD11;
  delay_ms(1);
  GPIOC->ODR &= ~GPIO_ODR_OD11;
  delay_ms(1);
}

static void send_nibble(uint8_t nibble)
{
  GPIOA->BSRR |= ((nibble >> 3) & 0x01) ? GPIO_BSRR_BS4 : GPIO_BSRR_BR4;
  GPIOA->BSRR |= ((nibble >> 2) & 0x01) ? GPIO_BSRR_BS1 : GPIO_BSRR_BR1;
  GPIOA->BSRR |= ((nibble >> 1) & 0x01) ? GPIO_BSRR_BS0 : GPIO_BSRR_BR0;
  GPIOC->BSRR |= (nibble & 0x01) ? GPIO_BSRR_BS12 : GPIO_BSRR_BR12;
  trigger_enable();
}
/// @brief Initialize HD44780
/// @param void
void HD44780_init(void)
{
  HD44780_gpio();
  HD44780_command(0x30);
  delay_ms(5);
  HD44780_command(0x30);
  delay_ms(1);
  HD44780_command(0x32); // configure lcd-4bits(0b10)
  HD44780_command(0x28); // configure 0010_1(n-lines-2)0(F*)0(*)0(*)-> 0x28
  HD44780_command(0x0C); // configure 0000_11(Display On)0(Cursor Off)0(Blink Off)-> 0x0C
  HD44780_command(0x01); // clear display
  HD44780_command(0x06); // configure 0000_011(Increment/Decrement RAM Address)0(Shift)-> 0x06
  delay_ms(100);
}

/// @brief Write a command 1-byte to HD44780
/// @param command uint8_t or Char
void HD44780_command(uint8_t command)
{
  // clear RS low
  GPIOC->ODR &= ~(GPIO_ODR_OD10);
  send_nibble((command >> 4) & 0x0F);
  send_nibble(command & 0x0F);
}
/// @brief Write a data 1-byte to HD44780
/// @param data uint8_t or Char
void HD44780_character(char data)
{
  GPIOC->ODR |= GPIO_ODR_OD10;
  send_nibble((data >> 4) & 0x0F);
  send_nibble(data & 0x0F);
}

/// @brief Position of the character in the LCD
/// @param x (uint8_t) position row (0)1 or (1) 2
/// @param y (uint8_t) position column (0)1-(15)16
void HD44780_xy(uint8_t x, uint8_t y)
{
  if (x > 0)
    HD44780_command(0xC0 + y);
  else
    HD44780_command(0x80 + y);
}

/// @brief Send a string to HD44780
/// @param str (char *)
void HD44780_string(char *str)
{
  while (*str != '\0')
  {
    HD44780_character(*str);
    str++;
  }
}

/// @brief Add to CGRAM of HD44780 the custom characters
/// @param addr_cgram uint8_t 0-7 position in CGRAM
void HD44780_CGRAM_addr(uint8_t addr_cgram)
{
  HD44780_command(0x40 + addr_cgram);
}

void HD44780_CGRAM(const char *str, uint8_t addr_cgram)
{
  HD44780_CGRAM_addr(addr_cgram * 8);
  for (uint8_t i = 8; i > 0; i--)
  {
    HD44780_character(*str);
    str++;
  }
}
