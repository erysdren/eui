
# static variables
CC = tcc
RM ?= rm -f

# base cflags
override CFLAGS += -DEUI_PIXEL_DEPTH=8

# executable name
EXEC ?= test_tcc

# objects
OBJECTS = test_basic.o eui.o

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
