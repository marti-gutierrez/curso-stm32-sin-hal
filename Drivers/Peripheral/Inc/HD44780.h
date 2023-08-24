#ifndef _INC_HD44780_H_
#define _INC_HD44780_H_

#include "main.h"
#include "SysTick.h"

// Rs_pin GPIOC_10 E_pin GPIOC_11 D4_pin GPIOA_0 D5_pin GPIOA_1 D6_pin GPIOA_4 D7_pin GPIOC_1

void HD44780_init(void);
void HD44780_command(uint8_t command);
void HD44780_character(char data);
void HD44780_xy(uint8_t x, uint8_t y);
void HD44780_string(char *str);
void HD44780_CGRAM_addr(uint8_t addr_cgram);
void HD44780_CGRAM(const char *str, uint8_t addr_cgram);

#endif // _INC_HD44780_H_