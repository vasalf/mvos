NAME        := kernel.bin
LIBS        := gcc

CC          := i686-elf-gcc
CFLAGS		:= -std=c99 -pipe -Wall -Wextra -Wshadow -ffreestanding -m32
CXX         :=
CXXFLAGS    :=
LD          := i686-elf-gcc
LDFLAGS     := -T src/linker.ld -ffreestanding -nostdlib
AS          := i686-elf-as
ASFLAGS     :=

# debug on
DEBUG_ON_CFLAGS         := -O0 -ggdb3 -DDEBUG
DEBUG_ON_CXXFLAGS       := -O0 -ggdb3 -DDEBUG
DEBUG_ON_LDFLAGS        := -O0 -ggdb3 -DDEBUG
DEBUG_ON_ASFLAGS        := --gen-debug

# debug off
DEBUG_OFF_CFLAGS        := -O2
DEBUG_OFF_CXXFLAGS      := -O2
DEBUG_OFF_LDFLAGS       := -O2
DEBUG_OFF_ASFLAGS       :=
