CC=gcc
TARGET=locadora
OBJS=main.o
CFLAGS=-Wall -pedantic -std=c99 -g

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

clear:
	rm -rf $(TARGET) *.o .*.o *~

run:
	@ ./$(TARGET)
