#ifndef _INC_RCC_H_
#define _INC_RCC_H_

#include "main.h"

#define PLL_P 0 // 00: PLLP = 2
#define PLL_N 180
#define PLL_M 4

void system_clock(void);

#endif /* _INC_RCC_H_ */