#ifndef _USART_H
#define _USART_H

void usart_init(void);
void usart_tx_char(char c);
void usart_tx_string(char *data);
char usart_rx_char(void);

#endif

// vim: tabstop=4 shiftwidth=4 autoindent
