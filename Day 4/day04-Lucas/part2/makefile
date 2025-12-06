CC = gcc
CFLAGS = -O2 -Wall
TARGET = solution-part-2

all: $(TARGET)

$(TARGET): solution.c
	$(CC) $(CFLAGS) -o $(TARGET) solution.c

clean:
	rm -f $(TARGET)

.PHONY: all clean