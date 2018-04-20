CC = gcc
CFLAGS = -Wall -ansi
TARGET = bank
OBJ = bank2.o
TARGET1 = wc
OBJ1 = wc.o
all: $(TARGET) $(TARGET1)

bank: $(OBJ)
	$(CC) $(CFLAGS) -o bank $(OBJ)

wc: $(OBJ1)
	$(CC) $(CFLAGS) -o wc $(OBJ1)

bank2.o: bank2.c
	$(CC) $(CFLAGS) -c bank2.c

wc.o: wc.c
	$(CC) $(CFLAGS) -c wc.c

clean:
	/bin/rm -f *.o (OBJ) $(TARGET) $(OBJ1) $(TARGET1)
