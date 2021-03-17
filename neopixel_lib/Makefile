CFLAGS = -Wall -Werror
OBJS_LIST = neopixel.o test_neopixel.o

all: test

clean:
	rm test $(OBJS_LIST)

test: $(OBJS_LIST)
	gcc $(CFLAGS) $(OBJS_LIST) -o $@

%.o: %.c
	gcc -c $(CFLAGS) $< -o $@

.PHONY: all clean

