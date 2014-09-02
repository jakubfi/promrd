#!/usr/bin/env python

import sys
import serial

port_name = "/dev/ttyUSB0"
port_rate = 9600

# ------------------------------------------------------------------------
def prom_read():

    # wait for start marker
    cnt = 0
    while cnt < 4:
        if s.read() == '-':
            cnt += 1

    # read and checksum 256 bytes
    data = bytearray(s.read(256))
    cksum = sum([k*v for (k,v) in zip(range(0,len(data)), data)]) % 0xffff

    return data, cksum

# ------------------------------------------------------------------------
def printout(data):
    for y in range(0, 4):
        out = "  "
        for x in range(0, 64):
            out = "%s%1x" % (out, data[y*64+x])
        print out

# ------------------------------------------------------------------------
def save(data, prefix, rid):
        f = open("%s-%04i.bin" % (prefix, rid), "wb")
        f.write(data)
        f.close()

# ------------------------------------------------------------------------
# ------------------------------------------------------------------------
# ------------------------------------------------------------------------

try:
    if len(sys.argv) > 3:
        raise SyntaxError
    prefix = sys.argv[1]
    count = int(sys.argv[2])
except:
    print "Usage: %s <prefix> <count>" % sys.argv[0]
    sys.exit(1)

try:
    s = serial.Serial(port_name, port_rate, serial.EIGHTBITS, serial.PARITY_NONE, serial.STOPBITS_ONE)
except:
    print "Cannot open serial port: %s" % port_name
    sys.exit(1)

print "Using port %s at %i baud" % (port_name, port_rate)

rdcnt = 10

ocksum = None
for rdcnt in range(0, count):
    print "  --- Readout #%-2i ------------------------------------------------" % (rdcnt+1)

    data, cksum = prom_read()

    printout(data)
    save(data, prefix, rdcnt)

    if ocksum is None:
        print "CKSUM: 0x%04x " % cksum
        ocksum = cksum
    elif cksum != ocksum:
        print "CKSUM: 0x%04x MISMATCH!" % cksum
    else:
        print "CKSUM: 0x%04x OK" % cksum

s.close()

# vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
