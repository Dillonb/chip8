CC=clang
CFLAGS=-Wall
LDFLAGS=-lm -lSDL2
TESTLDFLAGS=-lcmocka
DEPS=memory.h cpu.h display_tty.h display_sdl.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

OBJS=main.o memory.o cpu.o display_tty.o display_sdl.o
TESTOBJS=tests.o cpu.o memory.o

all: chip8

test: $(TESTOBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(TESTLDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

chip8: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -fv *.o *~ chip8 test
