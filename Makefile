CFLAGS = -O0 -w -ffunction-sections -fdata-sections -fno-fat-lto-objects -MMD -mmcu=atmega328p -DF_CPU=8000000L -std=c99
CC = avr-gcc
SRCDIR = ./src
BUILDDIR = ./build

$(shell mkdir -p $(BUILDDIR))

$(BUILDDIR)/main.hex: $(BUILDDIR)/main
	objcopy -O ihex -R .eeprom $^ $@

$(BUILDDIR)/main: $(BUILDDIR)/main.o
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/main.o: $(SRCDIR)/main.c
	$(CC) $(CFLAGS) -c $< -o $@

flash: $(BUILDDIR)/main
	avrdude -p m328p -c usbtiny -U $(BUILDDIR)/main

clean:
	rm -rf $(BUILDDIR)
