
# static variables
CC ?= gcc
RM ?= rm -f
PKGCONFIG ?= pkg-config

# base cflags and ldflags
override CFLAGS += $(shell $(PKGCONFIG) sdl2 --cflags)
override LDFLAGS += $(shell $(PKGCONFIG) sdl2 --libs)

# executable name
EXEC ?= test_sdl2_02

# objects
OBJECTS = test_sdl2_02.o eui.o eui_sdl2.o

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
