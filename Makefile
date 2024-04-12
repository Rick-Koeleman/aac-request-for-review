CC = gcc
CFLAGS = -Wall -Wextra
SOURCES = main.c i2c.c lis3mdl.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = app

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
