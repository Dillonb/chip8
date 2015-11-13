CC=clang
CFLAGS=-Wall
LDFLAGS=-lm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

OBJS=main.o memory.o cpu.o


all: chip8

%.o: %.c %.h
	$(CC) -c -o $@ $< $(CFLAGS)


chip8: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -fv *.o *~ chip8
