
# static variables
CC = wcl386
LD = wlink
RM ?= rm -f

# base cflags and ldflags
override CFLAGS += -DEUI_PIXEL_DEPTH=8 -bt=dos4g
override LDFLAGS += sys dos32x

# executable name
EXEC ?= test_watcom.exe

# objects
OBJECTS = test_watcom.obj eui.obj

# clean and build execs
all: clean $(EXEC)

# remove objects and executable
clean:
	$(RM) $(OBJECTS) $(EXEC)

# build executable
$(EXEC): $(OBJECTS)
	$(LD) name $@ $(foreach OBJ,$^,file $(OBJ)) $(LDFLAGS)

# generic c object rule
%.obj: %.c
	$(CC) -c $(CFLAGS) -fo=$@ $<
