CC = gcc
CFLAGS = --std=c2x -g -lm -Wall -Wextra -Wpedantic
TARGET = crep
SRCDIR = src
SOURCE = $(SRCDIR)/$(TARGET).c
TESTER = test/test.py

.PHONY: default
default: $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)

.PHONY: test
test:
	python $(TESTER)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $@ $<

