# Define variables
CC = gcc
CFLAGS = -Wall -g -std=c99   # Add -std=c99 to use the C99 standard
TARGET = my3proc

# The default rule that gets executed when running `make`
all: $(TARGET)

# Rule to build the target executable
$(TARGET): main3.o
	$(CC) $(CFLAGS) -o $(TARGET) main3.o

# Rule to compile main3.c into an object file
main3.o: main3.c
	$(CC) $(CFLAGS) -c main3.c

# Clean up generated files
clean:
	rm -f *.o $(TARGET)
