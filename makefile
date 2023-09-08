CC=gcc
TARGET=locadora
OBJS=locadora.c gutils.c
CFLAGS=-Wall -pedantic -std=c99

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

clear:
	rm -rf $(TARGET)