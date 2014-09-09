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

#include <util/delay.h>
#include <avr/io.h>
#include "usart.h"

#define A_DDR	DDRB
#define A_PORT	PORTB
#define CE_DDR	DDRA
#define CE_PORT	PORTA
#define O_DDR	DDRD
#define O_PORT	PORTD
#define O_PIN	PIND

// -----------------------------------------------------------------------
char prom_read(char addr)
{
	char d;
	A_PORT = addr;
	_delay_us(100); // just in case
	d = (O_PIN >> 2) & 0b1111;
	return d;
}

// -----------------------------------------------------------------------
int main(void)
{
	// initialize USART
	usart_init();

	// setup I/O ports
	A_DDR |= 0b11111111; // A0-A7 - outputs
	CE_DDR |= 0b00000011; // ~CE - outputs
	O_DDR &= 0b11000011; // O1-O4 - inputs
	O_PORT &= 0b11000011; // O1-O4 - no pull-ups

	A_PORT = 0;
	CE_PORT &= 0b11111100; // ~CE=0

	char data;

	// read and spit out the data
	while (1) {
		usart_tx_string("----");
		for (int addr=0 ; addr<256 ; addr++) {
			data = prom_read(addr);
			usart_tx_char(data);
		}
	}
} 

// vim: tabstop=4 shiftwidth=4 autoindent
