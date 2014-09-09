//  Copyright (c) 2014 Jakub Filipowicz <jakubf@gmail.com>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc.,
//  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

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
