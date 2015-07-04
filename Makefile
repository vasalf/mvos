SRCDIR=src
OBJDIR=obj
ISODIR=iso
SUBDIRS=$(SRCDIR) $(addprefix $(SRCDIR), /asm)
SUBDIRS_CLEAN=$(patsubst %,%.clean,$(SUBDIRS))

CC=i686-elf-gcc
CFLAGS=-std=c99 -O2 -Wall -Wextra -Wshadow -Werror -ffreestanding -I$(realpath $(SRCDIR))/include
AS=i686-elf-as
ASFLAGS=
LD=$(CC)
LDFLAGS=-T $(SRCDIR)/linker.ld -ffreestanding -O2 -nostdlib -lgcc
OBJS=$(wildcard $(addsuffix /$(OBJDIR)/*.o, $(SUBDIRS)))
export CC CFLAGS AS ASFLAGS OBJDIR



all: mvos.iso

mvos.iso: kernel.bin grub.cfg | $(ISODIR)
	mkdir -p $(ISODIR)/boot/grub
	cp kernel.bin $(ISODIR)/boot/kernel.bin
	cp grub.cfg $(ISODIR)/boot/grub/grub.cfg
	grub2-mkrescue -o $@ $(ISODIR)

kernel.bin: $(SUBDIRS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

$(SUBDIRS):
	$(MAKE) -C $@ all

$(SUBDIRS_CLEAN):
	$(MAKE) -C $(patsubst %.clean,%,$@) clean
.PHONY: $(SUBDIRS) $(SUBDIRS_CLEAN)

$(ISODIR):
	mkdir -p $(ISODIR)

clean: $(SUBDIRS_CLEAN)
	rm -rf $(ISODIR) mvos.iso kernel.bin

.PHONY: all clean
