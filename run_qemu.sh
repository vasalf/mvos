#!/bin/bash
qemu-system-x86_64 -machine type=pc,accel=kvm,kernel_irqchip=on -cpu host -boot order=cd -name mvos -cdrom mvos.iso $@
