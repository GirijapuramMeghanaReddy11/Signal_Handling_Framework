CC = gcc
CFLAGS = -Wall -Wextra
TARGET = signal_framework
SRC = src/signal_handling_framework.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)
