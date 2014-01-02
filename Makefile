CC=gcc
CFLAGS=-I

mnist_label_parser: mnist_label_parser.c hex_lib.c
	$(CC) mnist_label_parser.c hex_lib.c -o mnist_label_parser $(CFLAGS).

clean:
	rm mnist_label_parser
