# hexdump

A (simplified) clone of the `hexdump -c` command written in C.

## Usage

Compile as:
`gcc hexdump.c -o hexdump`
On the command line:
`./hexdump <file> [<count>]`
It will display the hexadecimal byte-by-byte contents of `<file>` and stop at either the end of the file or when `<count>` bytes have been displayed.

Example:
`./hexdump test.wav 10`

