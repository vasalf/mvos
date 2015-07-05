SRCDIR=src
OBJDIR=obj
ISODIR=iso
SUBDIRS=$(SRCDIR) $(addprefix $(SRCDIR), /asm)
OBJSUBDIRS=$(subst $(SRCDIR),$(OBJDIR),$(SUBDIRS))

CC=i686-elf-gcc
CFLAGS=-std=c99 -O2 -Wall -Wextra -Wshadow -Werror -ffreestanding -I$(realpath $(SRCDIR))/include
AS=i686-elf-as
ASFLAGS=
LD=$(CC)
LDFLAGS=-T $(SRCDIR)/linker.ld -ffreestanding -O2 -nostdlib -lgcc

C_SRCS=$(foreach subd,$(SUBDIRS),$(wildcard $(subd)/*.c))
C_OBJS=$(subst $(SRCDIR),$(OBJDIR),$(subst .c,.o,$(C_SRCS)))
AS_SRCS=$(foreach subd,$(SUBDIRS),$(wildcard $(subd)/*.s))
AS_OBJS=$(subst $(SRCDIR),$(OBJDIR),$(subst .s,.o,$(AS_SRCS)))
OBJS=$(C_OBJS) $(AS_OBJS)


all: mvos.iso

mvos.iso: kernel.bin $(SRCDIR)/grub.cfg | $(ISODIR)
	mkdir -p $(ISODIR)/boot/grub
	cp kernel.bin $(ISODIR)/boot/kernel.bin
	cp $(SRCDIR)/grub.cfg $(ISODIR)/boot/grub/grub.cfg
	grub2-mkrescue -o $@ $(ISODIR)

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
