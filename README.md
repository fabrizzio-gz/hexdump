# hexdump

A (simplified) clone of the `hexdump -c` command written in C.

## Usage

Compile and execute as:

`gcc hexdump.c -o hexdump`

`./hexdump <file> [<count>]`

It will display the hexadecimal byte-by-byte contents of `<file>` and stop at either the end of the file or when `<count>` bytes have been displayed.

## Examples

To print all bytes of `test.wav`:

`./hexdump test.wav`

To print only first 10 bytes of `test.wav`:

`./hexdump test.wav 10`

