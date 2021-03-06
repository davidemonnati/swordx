CC=gcc
HEADERDIR = include

vpath %.c src
vpath %.h $(HEADERDIR)

OBJDIR=obj
CFLAGS  = -g -Wall -I$(HEADERDIR)

all: swordx

swordx: $(OBJDIR)/swordx.o $(OBJDIR)/stack.o $(OBJDIR)/BST.o $(OBJDIR)/utils.o $(OBJDIR)/trie.o
	$(CC) $^ $(CFLAGS) -o $@

$(OBJDIR)/%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR)/swordx.o: swordx.c stack.c BST.c utils.c trie.c stack.h BST.h utils.h trie.h
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
