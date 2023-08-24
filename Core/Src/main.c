#include "main.h"
#include "RCC.h"
#include "HD44780.h"
#include "SysTick.h"

s_delay time;

const char customChar[] = {
    0x00,
    0x0A,
    0x0A,
    0x0A,
    0x00,
    0x11,
    0x0E,
    0x00};

int main(void)
{
  system_clock();
  SysTick_init(180000);
  HD44780_init();
  HD44780_CGRAM(customChar, 0);
  HD44780_xy(0, 8);
  HD44780_character('M');
  HD44780_xy(1, 0);
  HD44780_string("Hello World!");
  HD44780_xy(0, 0);
  HD44780_character(0);
  while (1)
  {
  }
  return 0;
}
