SRCDIR=src
OBJDIR=obj
ISODIR=iso
SUBDIRS=$(shell find $(SRCDIR) -type d | grep -v include)
INCLUDEDIRS=$(shell find $(SRCDIR) -type d -name include)
OBJSUBDIRS=$(subst $(SRCDIR),$(OBJDIR),$(SUBDIRS))

DEBUGFLAGS=-DDEBUG_THREADING

CC=i686-elf-gcc
CFLAGS=-std=c99 -O2 -Wall -Wextra -Wshadow -Werror -ffreestanding $(foreach inc,$(INCLUDEDIRS), -I$(realpath $(inc))) $(DEBUGFLAGS)
AS=i686-elf-as
ASFLAGS= -g
LD=$(CC)
LDFLAGS=-T $(SRCDIR)/linker.ld -ffreestanding -O2 -nostdlib -lgcc

SUFFIXES=.c .s
SRCS=$(foreach subd,$(SUBDIRS),$(foreach suf,$(SUFFIXES),$(wildcard $(subd)/*$(suf))))
OBJS=$(foreach subd,$(SUBDIRS),$(foreach suf,$(SUFFIXES),$(subst $(SRCDIR),$(OBJDIR),$(subst $(suf),.o,$(wildcard $(subd)/*$(suf))))))


all: mvos.iso

mvos.iso: kernel.bin $(SRCDIR)/grub.cfg | $(ISODIR)
	mkdir -p $(ISODIR)/boot/grub
	cp kernel.bin $(ISODIR)/boot/kernel.bin
	cp $(SRCDIR)/grub.cfg $(ISODIR)/boot/grub/grub.cfg
	grub2-mkrescue -o $@ $(ISODIR)
	rm /tmp/grub.*

kernel.bin: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJSUBDIRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.s | $(OBJSUBDIRS)
	$(AS) $(ASFLAGS) $< -o $@

$(OBJSUBDIRS) $(ISODIR):
	mkdir -p $@

tar: clean
	tar -zcvf ../mvos.tar.gz --exclude=./.git .
	@mv ../mvos.tar.gz mvos.tar.gz

clean:
	@rm -rf $(ISODIR) $(OBJDIR) mvos.iso kernel.bin mvos.tar.gz

.PHONY: all tar clean
