# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -Wextra 
FLEXFLAGS = 
BISONFLAGS = -d 
LDFLAGS = 

# Targets
TARGET = cpq

# Source files
BISON_SRC = parser.y
FLEX_SRC = lexer.l
C_SRCS = cpq.c translator.c symboltab.c error.c

# Generated files
BISON_OUT = parser.tab.c parser.tab.h
FLEX_OUT = lex.yy.c

# Object files
OBJS = lex.yy.o parser.tab.o cpq.o translator.o symboltab.o error.o

# Header dependencies (add error.h here if you create it)
DEPS = parser.tab.h translator.h symboltab.h error.h

# Default target
all: $(TARGET)

# Link all objects
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Flex rule
lex.yy.c: $(FLEX_SRC) $(DEPS)
	flex $<

# Bison rule
parser.tab.c parser.tab.h: $(BISON_SRC)
	bison $(BISONFLAGS) $<

# General compilation rule with header dependencies
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Special rule for translator.o to suppress unused-variable warning
translator.o: translator.c
	$(CC) $(CFLAGS) -Wno-unused-variable -c $< -o $@

# Clean
clean:
	rm -f $(TARGET) $(OBJS) $(BISON_OUT) $(FLEX_OUT) *.output

.PHONY: all clean