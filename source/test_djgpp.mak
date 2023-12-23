
# static variables
CC = i586-pc-msdosdjgpp-gcc
LD = i586-pc-msdosdjgpp-ld
AS = i586-pc-msdosdjgpp-as
RM ?= rm -f

# base cflags
override CFLAGS += -pedantic -Wall -Wextra

# executable name
EXEC ?= test_djgpp.exe

# objects
OBJECTS = test_djgpp.o eui.o

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
