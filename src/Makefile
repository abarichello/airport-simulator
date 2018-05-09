## Makefile da Simulacao de aeroporto.
CC=gcc
CFLAGS=-Wall -I. -lpthread -std=gnu11 -fno-stack-protector
EXEC=simulacao.out

all: $(EXEC)

%.o: %.c
	$(CC) -c $^ $(CFLAGS)

$(EXEC): main.o aeroporto.o aviao.o fila.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm *.o $(EXEC)
