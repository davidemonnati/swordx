CC=gcc

VPATH = src include
HEADERDIR = include

vpath %.c src
vpath %.h $(HEADERDIR)

OBJDIR=obj
CFLAGS  = -g -Wall -I$(HEADERDIR)

all: swordx

swordx: $(OBJDIR)/swordx.o $(OBJDIR)/stack.o $(OBJDIR)/test.o $(OBJDIR)/tree.o $(OBJDIR)/managefile.o 
	$(CC) $^ $(CFLAGS) -o $@

$(OBJDIR)/%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR)/swordx.o: swordx.c stack.c test.c tree.c managefile.c stack.h test.h tree.h managefile.h
	$(CC) $(CFLAGS) -o $@ -c $<

.PONY: install uninstall clean

install:
	@echo "Installazione in corso..."
	@cp ./swordx /usr/local/bin/swordx
	@echo "Installazione terminata." 

uninstall:
	@echo "Disinstallazione swordx in corso..."
	@rm /usr/local/bin/swordx
	@echo "Disinstallazione completata."

clean:
	rm $(OBJDIR)/*.o swordx
