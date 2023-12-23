
# static variables
CC = ia16-elf-gcc
LD = ia16-elf-ld
AS = ia16-elf-as
RM ?= rm -f

# base cflags
override CFLAGS += -pedantic -Wall -Wextra -DEUI_PIXEL_DEPTH=8

# executable name
EXEC ?= test_ia16.com

# objects
OBJECTS = test_ia16.o eui.o

# clean and build execs
all: clean $(EXEC)

# remove objects and executable
clean:
	$(RM) $(OBJECTS) $(EXEC)

# build executable
$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

# generic c object rule
%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<
