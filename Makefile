OBJDIR=./.tmp
ISODIR=./isodir
SRCDIR=./src

CC=i686-elf-gcc
CFLAGS=--std=c99 -O2 -Wall -Wextra -Wshadow -Werror -ffreestanding
LFLAGS=-T $(SRCDIR)/linker.ld -ffreestanding -O2 -nostdlib -lgcc
AS=i686-elf-as
ASFLAGS=

OBJS=$(OBJDIR)/kernel.o $(OBJDIR)/stdstring.o $(OBJDIR)/vga.o $(OBJDIR)/boot.o $(OBJDIR)/ports.o $(OBJDIR)/system.o $(OBJDIR)/keyboard.o


all: iso clean_compilation


iso: kernel
	mkdir -p $(ISODIR)/boot/grub
	mv kernel.bin $(ISODIR)/boot/kernel.bin
	cp grub.cfg $(ISODIR)/boot/grub/grub.cfg
	grub2-mkrescue -o mvos.iso $(ISODIR)


kernel: $(OBJDIR) $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o kernel.bin


$(OBJDIR):
	mkdir -p $(OBJDIR)


$(OBJDIR)/kernel.o: $(SRCDIR)/kernel.c
	$(CC)  $(CFLAGS) -c $(SRCDIR)/kernel.c -o $(OBJDIR)/kernel.o


$(OBJDIR)/stdstring.o: $(SRCDIR)/stdstring.c $(SRCDIR)/include/stdstring.h
	$(CC)  $(CFLAGS) -c $(SRCDIR)/stdstring.c -o $(OBJDIR)/stdstring.o
	

$(OBJDIR)/vga.o: $(SRCDIR)/vga.c $(SRCDIR)/include/vga.h
	$(CC)  $(CFLAGS) -c $(SRCDIR)/vga.c -o $(OBJDIR)/vga.o


$(OBJDIR)/ports.o: $(SRCDIR)/ports.c $(SRCDIR)/include/ports.h
	$(CC)  $(CFLAGS) -c $(SRCDIR)/ports.c -o $(OBJDIR)/ports.o


$(OBJDIR)/system.o: $(SRCDIR)/system.c $(SRCDIR)/include/system.h
	$(CC)  $(CFLAGS) -c $(SRCDIR)/system.c -o $(OBJDIR)/system.o


$(OBJDIR)/boot.o: $(SRCDIR)/boot.s
	$(AS) $(ASFLAGS) $(SRCDIR)/boot.s -o $(OBJDIR)/boot.o


$(OBJDIR)/keyboard.o: $(SRCDIR)/keyboard.c $(SRCDIR)/include/keyboard.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/keyboard.c -o $(OBJDIR)/keyboard.o


clean_compilation:
	rm -rf $(ISODIR)


clean: clean_compilation
	rm -rf $(OBJDIR)
	rm -f mvos.iso


.PHONY: all clean_compilation clean
