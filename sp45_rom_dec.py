#!/usr/bin/env python3

import sys

def load(fname):
    f = open(fname, "rb")
    x = f.read()
    f.close()
    v = [ (~int(z))&0xf for z in x ]
    return v

if len(sys.argv) != 2:
    print("Usage: " + sys.argv[0] + " <version>")
    sys.exit(1)

version = sys.argv[1]

t1 = load("sp45de_" + version + "_01-04.bin")
t2 = load("sp45de_" + version + "_05-08.bin")
t3 = load("sp45de_" + version + "_09-12.bin")
t4 = load("sp45de_" + version + "_13-16.bin")

f = open("sp45de_" + version + "_merged.bin", "wb")

for i in range(256):
    v = (t4[i] << 12) | (t3[i] << 8) | (t2[i] << 4) | (t1[i] << 0)
    print("0x%04x" % v)
    f.write(bytes([v&0xff, (v>>8)&0xff]))

f.close()
