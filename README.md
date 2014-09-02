
About PROMRD
=============================================

Promrd is a set of tools built for getting contents of Amepol's RTC PROM memory out. It consists of three parts:

* simple PROM reader based on ATtiny2313
* software for the ATtiny2312
* python receiver script to read and store the data

Circuit
-------------------------------

Amepol's timer PROM memory is a set of 3 Signetics 82S129 bipolar 256x4 bit PROM chips. It connects to an ATtiny2313 in a following way:

* pins B0-B7 - address lines A0-A7
* pins D2-D5 - data lines O1-O4
* pins A0-A1 - ~CE1 and ~CE2

Connection to a PC is done through an FT232 FTDI or similar device connected to RxD/TxD pins (D0-D1).

MCU needs to be configured with 8MHz clock.

ATtiny software
-------------------------------

After power-up, ATtiny simply starts to spit out contents of the PROM in an endless loop, marking the beginning of each loop with four '-' characters and sleeping for a second after each loop.

Receiver script
-------------------------------

Receiver script waits for "----" on the serial line and then collects next 256 bytes that appear on the line. Each byte stores 4 bits read from the PROM memory on positions 0-3. After each loop checksum is printed out and data is stored in a file.

Commandline syntax is:

```
      promrd.py prefix copies
```

where:

* prefix - prefix for output files. Files are suffixed with sequential copy numbers
* copies - number of PROM reads

