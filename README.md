Promrd is a set of tools built for getting contents of Amepol's RTC PROM memory out. It consists of four parts:

* simple PROM reader based on ATtiny2313
* software for the ATtiny2312
* python receiver script to read and store the data
* python decoder script to make a binary program from given PROM contents

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
 promrd.py <prefix> <copies>
```

where:

* *prefix* - prefix for output files. Files are suffixed with sequential copy numbers
* *copies* - number of PROM reads

Decoder script
-------------------------------

Receiver script produce files that store only half a byte (per chip).
Two files with contents of chips "A" and "B" need to be concatenated to form a proper byte sequence.
Additionaly, three consequent bytes from the sequence are needed to form one machine word.
Byte contents are as follows:

1. P V x E d d d d  =>  machine word bits 0-3
2. P V d d d d d d  =>  machine word bits 4-9
3. P V d d d d d d  =>  machine word bits 10-15

where:

* P - parity
* V - byte validity (1=valid)
* x - ignored
* E - data end (V=1 and E=1 means EOF)
* d - data bits

Decoder script does all the mentioned decoding and writes binary file with the actual program stored on PROM chips.

Commandline syntax is:

```
 promdc.py <prom_a> <prom_b> <output>
```

where:

* *prom_a* - contents of PROM "A" chip
* *prom_b* - contents of PROM "B" chip
* *output* - binary output filename

