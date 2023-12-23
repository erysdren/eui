
# static variables
CC=wcc386
LD=wlink
RM=rm -f

# base system and cflags
SYS=dos32x
CFLAGS=-DEUI_PIXEL_DEPTH=8 -bt=$(SYS)

# executable name
TARGET=test_watcom.exe

# objects
OBJECTS=test_watcom.obj eui.obj

# clean and build executable
all: clean $(TARGET)

# remove objects and executable
clean: .SYMBOLIC
	$(RM) $(OBJECTS) $(TARGET)

# build executable
$(TARGET): $(OBJECTS) $(TARGET).lnk
	$(LD) @$(TARGET).lnk

# link file
$(TARGET).lnk:
	echo name $(TARGET) >$(TARGET).lnk
	echo system $(SYS) >>$(TARGET).lnk
	for %i in ($(OBJECTS)) do echo file %i >>$(TARGET).lnk

# generic c object rule
.c.obj:
	$(CC) $(CFLAGS) $*.c -fo=$*.obj
