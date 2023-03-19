# Zara Purewal - 21404176
# ca216/myshell
# I acknowledge DCU's Academic Integrity Policy

# Set the destination directory for the executable
DESTDIR = ../bin

# Set the name of the executable
EXECUTABLE = myshell

# Set the compiler and compiler options
CC = gcc
CFLAGS = -Wall

# List the source files
SRCS = myshell.c

# Derive the object files from the source files
OBJS = $(SRCS:.c=.o)

# Set the default target
all: $(EXECUTABLE)

# Rule to build the executable
$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(DESTDIR)/$(EXECUTABLE)

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(DESTDIR)/$(EXECUTABLE)

