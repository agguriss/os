CC      = gcc
CFLAGS  = -Wall -g
LIBS    = -lpthread

SRCS    = $(wildcard *.c)
TARGETS = $(SRCS:.c=)

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f $(TARGETS)

.PHONY: all clean