CFLAGS = -ffunction-sections -fdata-sections -fno-fat-lto-objects -MMD -std=c11 -I../src -DIN_SIMULATOR -std=c11 -lraylib -lpthread

CC = gcc
SRCDIR = ../src
BUILDDIR = ./build

$(shell mkdir -p $(BUILDDIR))

OBJS = \
	   $(BUILDDIR)/main.o \
	   $(BUILDDIR)/font.o \
	   $(BUILDDIR)/counters.o \
	   $(BUILDDIR)/Assert.o \
	   $(BUILDDIR)/hardware_sim.o


$(BUILDDIR)/main: $(OBJS)
	$(CC) $^ $(CFLAGS) -o $@

$(BUILDDIR)/hardware_sim.o: hardware_sim.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)

.PHONY: run

run: $(BUILDDIR)/main
	$(BUILDDIR)/main

