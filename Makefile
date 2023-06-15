CFLAGS = -O0 -w -ffunction-sections -fdata-sections -fno-fat-lto-objects -MMD -mmcu=atmega328p -DF_CPU=8000000L -std=c99
CC = avr-gcc
SRCDIR = ./src
BUILDDIR = ./build

$(shell mkdir -p $(BUILDDIR))

OBJS = \
	   $(BUILDDIR)/main.o \
	   $(BUILDDIR)/font.o \
	   $(BUILDDIR)/hardware.o


$(BUILDDIR)/main.hex: $(BUILDDIR)/main
	objcopy -O ihex -R .eeprom $^ $@

$(BUILDDIR)/main: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

flash: $(BUILDDIR)/main
	avrdude -p m328p -c usbtiny -U $<

clean:
	rm -rf $(BUILDDIR)

