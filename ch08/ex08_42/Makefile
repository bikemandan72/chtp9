CC = gcc
CFLAGS = -Wall -lm -g
#export CFLAGS
SRCS = cipher_test.c 

.PHONY: all clean

all: $(SRCS:.c=)

clean:
	rm -rf $(SRCS:.c=)

$(SRCS:.c=): $(SRCS) cipher.c cipher.h
	$(CC) $^ -o $@ $(CFLAGS)