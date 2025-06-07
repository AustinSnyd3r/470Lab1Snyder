# Flags
CC = gcc
CFLAGS = -Wall

# Source files
SRCS = Austin_libFS.c Austin_testfile.c

# Object files 
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = Lab4

# Default target (run when you type 'make')
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile .c files into .o files
%.o: %.c Austin_libFS.h
	$(CC) $(CFLAGS) -c $< -o $@
