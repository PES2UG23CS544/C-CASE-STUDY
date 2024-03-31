CC = gcc  
CFLAGS = -Wall -g  

# Target (executable name)
TARGET = supermarket

# Source files
SOURCES = main.c

# Object files (automatically generated based on source files)
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Compile each source file into its corresponding object file
%.o: %.c
    $(CC) $(CFLAGS) -c $<  # Use $< for automatic source dependency

clean:
    rm -f $(OBJECTS) $(TARGET)
