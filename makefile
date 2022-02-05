hexdump: src/hexdump.c
	gcc -o hexdump -Wall src/hexdump.c

clean:
	rm hexdump
