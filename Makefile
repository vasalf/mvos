all: kernel iso clean_compilation

compile_kernel:
	if [ ! -d ".tmp" ]; then mkdir .tmp; fi
	# Compile GAS files
	i686-elf-as     ./src/boot.s     -o ./.tmp/boot.o
	# Compile C files
	i686-elf-gcc    ./src/kernel.c      -o ./.tmp/kernel.o      -c --std=c99 -ffreestanding -O2 -Wall -Wextra -Wshadow -Werror
	i686-elf-gcc    ./src/stdstring.c   -o ./.tmp/stdstring.o   -c --std=c99 -ffreestanding -O2 -Wall -Wextra -Wshadow -Werror
	i686-elf-gcc    ./src/vga.c         -o ./.tmp/vga.o         -c --std=c99 -ffreestanding -O2 -Wall -Wextra -Wshadow -Werror

link_kernel:
	i686-elf-gcc -T ./src/linker.ld -ffreestanding -O2 -nostdlib -lgcc ./.tmp/stdstring.o ./.tmp/vga.o ./.tmp/boot.o ./.tmp/kernel.o -o kernel.bin

kernel: compile_kernel link_kernel

iso:
	mkdir -p ./isodir/boot/grub
	mv kernel.bin ./isodir/boot/kernel.bin
	cp grub.cfg ./isodir/boot/grub/grub.cfg
	grub2-mkrescue -o mvos.iso isodir

clean_compilation:
	rm -Rf .tmp isodir

clean: clean_compilation
	rm -f mvos.iso

.PHONY: all clean
