# Compiler and flags
CC = gcc
CFLAGS = -g -Wall -Wextra
FLEXFLAGS =  # Flex doesn't support -W flags directly
BISONFLAGS = -d
LDFLAGS = 

# Targets
TARGET = cpq

# Source files
BISON_SRC = parser.y
FLEX_SRC = lexer.l
C_SRCS = cpq.c translator.c symboltab.c

# Generated files
BISON_OUT = parser.tab.c parser.tab.h
FLEX_OUT = lex.yy.c

# Object files
OBJS = lex.yy.o parser.tab.o cpq.o translator.o symboltab.o

# Default target
all: $(TARGET)

# Link all objects
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Flex rule (suppress warnings via %option in .l file)
lex.yy.c: $(FLEX_SRC) parser.tab.h
	flex $<

# Bison rule
parser.tab.c parser.tab.h: $(BISON_SRC)
	bison $(BISONFLAGS) $<

# Compile .c to .o (suppress unused-variable only for translator.c)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Special rule for translator.o to suppress unused-variable warning
translator.o: translator.c
	$(CC) $(CFLAGS) -Wno-unused-variable -c $< -o $@

# Clean
clean:
	rm -f $(TARGET) $(OBJS) $(BISON_OUT) $(FLEX_OUT) *.output

.PHONY: all clean