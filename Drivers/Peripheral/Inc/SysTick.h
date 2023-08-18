#ifndef _INC_SYSTICK_H_
#define _INC_SYSTICK_H_

#include "main.h"

static volatile uint32_t ms_tick = 0;

typedef struct s_delay
{
  uint32_t start_time;
  uint32_t duration;
  bool running;
} s_delay;

void SysTick_init(uint32_t systick_value);
void SysTick_Handler(void);
void ms_inc_tick(void);          // increment ms_tick
uint32_t get_ms_ticks(void);     // return of value of ms_tick
void delay_ms(uint32_t time_ms); // create delay

void delay_ms_NB(s_delay *delay, uint32_t time_ms);
bool delay_read(s_delay *delay);

#endif /*_INC_SYSTICK_H_*/