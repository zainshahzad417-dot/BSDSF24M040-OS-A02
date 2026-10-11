.RECIPEPREFIX :=>
CC=gcc
CFLAGS=-Wall -Wextra -std=c11 -g
SOURCE=src/ls-v1.0.0.c
OBJECT=obj/ls.o
TARGET=bin/ls
.PHONY:all clean
all:$(TARGET)
$(TARGET):$(OBJECT)
>mkdir -p bin
>$(CC) $(CFLAGS) $(OBJECT) -o $(TARGET)
$(OBJECT):$(SOURCE)
>mkdir -p obj
>$(CC) $(CFLAGS) -c $(SOURCE) -o $(OBJECT)
clean:
>rm -f $(OBJECT) $(TARGET)

