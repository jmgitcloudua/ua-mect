# # Make file for c programs

# CFLAGS= -DNDEBUG

# # source files

# SRC = $(wildcard *.c)

# # object files

# OBJ = $(SRC:.c=.o)

# # executable files

# EXE = $(SRC:.c=)

# # compiler

# CC = gcc

# # compiler flags

# CFLAGS = -Wall -g

# # linker flags

# LDFLAGS = -lm

# # default target

# all: $(EXE)

# # link

# %: %.o
# 	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

# # compile

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $<

# # clean

# clean:
# 	rm -f $(OBJ) $(EXE) *~

# # end of file

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
