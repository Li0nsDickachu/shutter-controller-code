CFLAGS = -w -ffunction-sections -fdata-sections -fno-fat-lto-objects -MMD -std=c99 -lraylib -I../src
CC = gcc
SRCDIR = ../src
BUILDDIR = ./build

$(shell mkdir -p $(BUILDDIR))

OBJS = \
	   $(BUILDDIR)/main.o \
	   $(BUILDDIR)/font.o \
	   $(BUILDDIR)/hardware_sim.o


$(BUILDDIR)/main: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/hardware_sim.o: hardware_sim.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

flash: $(BUILDDIR)/main
	avrdude -p m328p -c usbtiny -U $<

clean:
	rm -rf $(BUILDDIR)

