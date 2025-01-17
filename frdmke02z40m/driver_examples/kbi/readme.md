Overview
========
The KBI Example project is a demonstration program that uses the KSDK software to use
keyboard interrupt.
The example uses one KBI pin to generate a raising edge interrupt to show the example.

SDK version
===========
- Version: 2.15.0

Toolchain supported
===================
- GCC ARM Embedded  12.2
- MCUXpresso  11.8.0

Hardware requirements
=====================
- Mini USB cable
- Two FRDM-KE02Z boards
- Personal Computer

Board settings
==============
connect 2# & 6# on J2.

Prepare the Demo
================
1.  Connect a mini USB cable between the PC host and the OpenSDA USB port on the board.
2.  Open a serial terminal on PC for OpenSDA serial device with these settings:
    - 115200 baud rate
    - 8 data bits
    - No parity
    - One stop bit
    - No flow control
3.  Download the program to the target board.
4.  Reset the SoC and run the project.

Running the demo
================
When the demo runs successfully, the log would be seen on the OpenSDA terminal like:

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 KBI Driver Example Start.

 The KBI keyboard interrupt has happened!

 KBI Driver Example End.

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
