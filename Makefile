CC=clang
CFLAGS=-Wall
LDFLAGS=-lm -lSDL2

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

OBJS=main.o memory.o cpu.o display_tty.o display_sdl.o


all: chip8

%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)


chip8: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -fv *.o *~ chip8
