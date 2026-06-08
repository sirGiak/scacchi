CC = gcc
CFLAGS = -g -Wall
TARGET = scacchi.out
OBJS = scacchi.o utils.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET)

.PHONY: all clean
