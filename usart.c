#include <util/setbaud.h>
#include <avr/io.h>

// -----------------------------------------------------------------------
void usart_init(void)
{
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
#if USE_2X
	UCSRA |= (1 << U2X);
#else
	UCSRA &= ~(1 << U2X);
#endif
	UCSRB = (1 << TXEN) | (1 << RXEN);
	UCSRC = (1 << UCSZ1) | (1 << UCSZ0);
}

// -----------------------------------------------------------------------
void usart_tx_char(char c)
{
	while (!(UCSRA & (1 <<UDRE)));
	UDR = c;
}

// -----------------------------------------------------------------------
void usart_tx_string(char *data)
{
	while ((*data != '\0')) {
		usart_tx_char(*data);
		data++;
	}   
}

// -----------------------------------------------------------------------
char usart_rx_char(void)
{
	while (!(UCSRA & (1<<RXC)));
	return UDR;
}

// vim: tabstop=4 shiftwidth=4 autoindent
