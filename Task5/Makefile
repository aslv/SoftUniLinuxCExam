CC=gcc #compiler

CFLAGS=-c -Wall -O # compiler flags
# -c: compile
# -Wall: warnings
# -O: optimize code

LDFLAGS=-lm # linker flags
# -lm: will use math.h

SOURCES=main.c calc.c figure.c
OBJECTS=$(SOURCES:.c=.o)

EXECUTABLE=main

# useful for updating .o files when .h files are modified
CALC_H=main.o calc.o
FIGURE_H=main.o figure.o
DEFINES_H=main.o calc.o figure.o

# a rule
all: $(SOURCES) $(EXECUTABLE)
# to build all, it must furst build sources and executable

# another rule
$(EXECUTABLE):$(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o %@
# to create executable, it must first build objecys
# and then run the command

# recompiling .o files when libs are modified
$(CALC_H): calc.h
$(FIGURE_H): figure.h
$(DEFINES_H): defines.h

# a pattern rule
.c.o:
	$(CC) $(CFLAGS) $< -o $@
# in order to build objects, first rebuild .c
# and run the command

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
# removing objects and executable

