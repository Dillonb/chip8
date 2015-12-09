CC=clang
CFLAGS=-Wall -I/usr/local/include
LDFLAGS=-lm -lSDL2 -lSDL2_ttf -L/usr/local/lib
TESTLDFLAGS=-lcmocka
DEPS=memory.h cpu.h display_tty.h display_sdl.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

OBJS=main.o memory.o cpu.o display_tty.o display_sdl.o
TESTOBJS=tests.o cpu.o memory.o 

all: chip8

test: $(TESTOBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS) $(TESTLDFLAGS)
	./test

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

chip8: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -fv *.o *~ chip8 test

run: clean all
	./chip8 games/Space\ Invaders\ \[David\ Winter\].ch8
