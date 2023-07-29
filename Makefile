CC = gcc
CFLAGS = --std=c2x -g -lm -Wall -Wextra -Wpedantic
TARGET = crep
SRCDIR = src
SOURCE = $(SRCDIR)/$(TARGET).c

.PHONY: default
default: $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: test
test: default
	cd test && python test.py

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $<

