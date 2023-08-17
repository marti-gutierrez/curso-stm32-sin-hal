#ifndef _INC_GPIO_H_
#define _INC_GPIO_H_

#include "main.h"

typedef enum
{
  low,
  high
} e_state;

void gpio_led_init(void);
void gpio_led_write(e_state state);
void gpio_led_toggle(void);
void gpio_btn_init(void);
e_state gpio_btn_read(void);

#endif /* _INC_GPIO_H_*/