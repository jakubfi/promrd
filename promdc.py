#!/usr/bin/env python
# -*- coding: UTF-8 -*-

#  Copyright (c) 2014 Jakub Filipowicz <jakubf@gmail.com>
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc.,
#  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

import sys

if len(sys.argv) != 4:
    print "Usage: %s <prom_a> <prom_b> <output>" % sys.argv[0]
    sys.exit(1)

# read prom A
fa = open(sys.argv[1], "rb");
a = bytearray(fa.read(256))
fa.close()

# read prom B
fb = open(sys.argv[2], "rb");
b = bytearray(fb.read(256))
fb.close()

# decode everything and write output
fo = open(sys.argv[3], "wb")
shift = 12
d = 0
for i in range(0, 256):
    # make byte value from 4-bit prom A and B contents
    v = (a[i] << 4) | b[i]

    # skip invalid bytes
    if v & 0b01000000 == 0:
        continue;

    # EOF
    if shift == 12 and v & 0b01010000 == 0b01010000:
        break;

    # collect 16-bit machine word
    d |= (v & 0b111111) << shift

    shift -= 6;
    if shift < 0:
        fo.write(chr(d >> 8))
        fo.write(chr(d & 255))
        shift = 12
        d = 0

fo.close();

# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
