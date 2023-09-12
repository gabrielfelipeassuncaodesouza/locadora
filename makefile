TARGET=locadora

SRC_DIR=./src
C_SRC=$(wildcard $(SRC_DIR)/*.c)

OBJS=$(C_SRC:.c=.o)
OBJS_TEST=$(subst ./src/main.o, ./tests/test.o, $(OBJS))

CC=gcc
CFLAGS=-I$(SRC_DIR) -Wall -pedantic -std=c99 -g

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(CFLAGS)

test: $(OBJS_TEST)
	$(CC) -o test $(OBJS_TEST) $(CFLAGS)
	@ ./test

clear:
	rm -rf $(TARGET) *.o .*.o *~ $(SRC_DIR)/*.o $(SRC_DIR)/.*.o ./tests/*.o ./tests/.*.o

run:
	@ ./locadora
