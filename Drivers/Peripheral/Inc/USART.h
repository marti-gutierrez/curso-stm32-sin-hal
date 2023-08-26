#ifndef _INC_USART_H_
#define _INC_USART_H_

#include "main.h"

#define CLOCK_USART2 45000000UL

void USART_init(uint32_t BAUD);
void USART_tx(char data);
char USART_rx(void);
void USART_tx_str(char *str);
bool USART_rx_str(char *str, uint32_t len, uint32_t timeout);

#endif /* _INC_USART_H_  */