# CC = gcc
# CFLAGS = -O2 -Wall -std=c99 
# LDFLAGS =

# LIBS = -lm

# EXECUTABLE = main 

# SRCFILES = $(wildcard *.c)
# OBJFILES = $(SRCFILES:.c=.o)   

# $(EXECUTABLE): $(OBJFILES) 
# 	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

# .PHONY: clean

# clean: 
# 	rm -f $(EXECUTABLE) $(OBJFILES)

# Compiler and flags
# CC := gcc
# CFLAGS := -O2 -Wall -std=c99 
# LDFLAGS := 
# LIBS := -lm

# # Executable name
# EXECUTABLE := main

# # Source files
# SRC := $(wildcard *.c)
# # Object files
# OBJ := $(SRC:.c=.o)

# # Build executable
# $(EXECUTABLE): $(OBJ)
# 	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

# # Compile source files into object files
# %.o: %.c
# 	$(CC) $(CFLAGS) -c -o $@ $<

# .PHONY: clean

# clean:
# 	rm -f $(EXECUTABLE) $(OBJ)

# # Dependencies
# -include $(OBJ:.o=.d)

# # Generate dependency files during compilation
# %.d: %.c
# 	@$(CC) $(CFLAGS) -MM -MT $(@:.d=.o) $< > $@

# # Target to generate dependency files
# depend: $(OBJ:.o=.d)

# # Usage information
# help:
# 	@echo "Makefile targets:"
# 	@echo "  all (default): Build the executable"
# 	@echo "  clean: Clean up generated files"
# 	@echo "  depend: Generate dependency files"

# # Default target
# all: $(EXECUTABLE)

# # Silence make
# .SILENT: clean help

# Compiler and flags
CC := gcc
CFLAGS := -O2 -Wall -std=c99
LDFLAGS :=
LIBS := -lm

# Source files
SRCS := $(wildcard *.c)

# Executables (replace '.c' with '.out' for example)
EXES := $(patsubst %.c,%,$(SRCS))

# Build all executables
all: $(EXES)

# Rule to build each executable
%: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LIBS)

.PHONY: clean

clean:
	rm -f $(EXES)
	rm -f *.o
