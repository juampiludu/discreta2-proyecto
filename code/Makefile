CC = gcc
CPROD = -O3
CDEBUG = -g -DNDEBUG -fsanitize=address,undefined
CFLAGS = -Wall -Wextra -std=c99 $(CPROD)
SOURCES = main.c EstructuraGrafo24.c ColoreoGrafo.c
OBJECTS = $(SOURCES:.c=.o)
TARGET = grafo

.PHONY: all win clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)
