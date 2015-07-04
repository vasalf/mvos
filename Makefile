OBJDIR=./obj
ISODIR=./iso
SRCDIR=./src

CC=i686-elf-gcc
CFLAGS=--std=c99 -O2 -Wall -Wextra -Wshadow -Werror -ffreestanding -Isrc/include
LFLAGS=-T $(SRCDIR)/linker.ld -ffreestanding -O2 -nostdlib -lgcc
AS=i686-elf-as
ASFLAGS=

OBJS=$(OBJDIR)/kernel.o $(OBJDIR)/string.o $(OBJDIR)/vga.o $(OBJDIR)/boot.o $(OBJDIR)/ports.o $(OBJDIR)/system.o $(OBJDIR)/keyboard.o $(OBJDIR)/registers.o $(OBJDIR)/init.o $(OBJDIR)/lidt.o $(OBJDIR)/lgdt.o $(OBJDIR)/idt.o $(OBJDIR)/gdt.o $(OBJDIR)/pic.o $(OBJDIR)/asm_isr.o $(OBJDIR)/isr.o $(OBJDIR)/asm_irq.o $(OBJDIR)/irq.o $(OBJDIR)/timer.o

all: iso


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

$(OBJDIR)/string.o: $(SRCDIR)/string.c $(SRCDIR)/include/string.h
	$(CC)  $(CFLAGS) -c $(SRCDIR)/string.c -o $(OBJDIR)/string.o

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

$(OBJDIR)/registers.o: $(SRCDIR)/registers.s $(SRCDIR)/include/registers.h
	$(AS) $(ASFLAGS) $(SRCDIR)/registers.s -o $(OBJDIR)/registers.o

$(OBJDIR)/init.o: $(SRCDIR)/init.c $(SRCDIR)/include/init.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/init.c -o $(OBJDIR)/init.o

$(OBJDIR)/lidt.o: $(SRCDIR)/lidt.s
	$(AS) $(ASFLAGS) $(SRCDIR)/lidt.s -o $(OBJDIR)/lidt.o

$(OBJDIR)/idt.o: $(SRCDIR)/idt.c $(SRCDIR)/include/idt.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/idt.c -o $(OBJDIR)/idt.o

$(OBJDIR)/gdt.o: $(SRCDIR)/gdt.c $(SRCDIR)/include/gdt.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/gdt.c -o $(OBJDIR)/gdt.o

$(OBJDIR)/lgdt.o: $(SRCDIR)/lgdt.s $(SRCDIR)/include/lgdt.h
	$(AS) $(ASFLAGS) $(SRCDIR)/lgdt.s -o $(OBJDIR)/lgdt.o

$(OBJDIR)/pic.o: $(SRCDIR)/pic.c $(SRCDIR)/include/pic.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/pic.c -o $(OBJDIR)/pic.o

$(OBJDIR)/isr.o: $(SRCDIR)/isr.c $(SRCDIR)/include/isr.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/isr.c -o $(OBJDIR)/isr.o

$(OBJDIR)/asm_isr.o: $(SRCDIR)/asm_isr.s $(SRCDIR)/include/asm_isr.h
	$(AS) $(ASFLAGS) $(SRCDIR)/asm_isr.s -o $(OBJDIR)/asm_isr.o

$(OBJDIR)/asm_irq.o: $(SRCDIR)/asm_irq.s $(SRCDIR)/include/asm_irq.h
	$(AS) $(ASFLAGS) $(SRCDIR)/asm_irq.s -o $(OBJDIR)/asm_irq.o

$(OBJDIR)/irq.o: $(SRCDIR)/irq.c $(SRCDIR)/include/irq.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/irq.c -o $(OBJDIR)/irq.o

$(OBJDIR)/timer.o: $(SRCDIR)/timer.c $(SRCDIR)/include/timer.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/timer.c -o $(OBJDIR)/timer.o

clean_compilation:
	rm -rf $(ISODIR)


clean: clean_compilation
	rm -rf $(OBJDIR)
	rm -f mvos.iso


.PHONY: all clean_compilation clean
