TARGET = ls
CC = cc
CFLAGS  = -g -Wall -Werror -Wextra
RM = rm -f

default: $(TARGET)
all: default

$(TARGET): ls.o cmp.o helper.o
	$(CC) $(CFLAGS) -o $(TARGET) ls.o cmp.o helper.o

ls.o: ls.c ls.h
	$(CC) $(CFLAGS) -c ls.c

cmp.o: cmp.c cmp.h
	$(CC) $(CFLAGS) -c cmp.c

helper.o: helper.c helper.h
	$(CC) $(CFLAGS) -c helper.c

clean:
	$(RM) $(TARGET) *.o 
