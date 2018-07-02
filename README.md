Minux
===
Minux is a hobby OS that I am making for my Operating Systems class at Drexel. It is mostly an exploratory look into how Operating Systems work.

It currently only supports compilationn to x64 targets.

Dependencies
---
- QEMU
- Binutils cross-compiled to x86_64 arch with the following flags: `./configure --target=x86_64-elf --prefix="$HOME/opt/cross" --disable-nls --disable-werror --disable-libdecnumber --disable-readline --disable-sim`
- NASM
- GRUB2

Building the ISO
---
Run `make` to compile the files and create an ISO

Running the OS
---
Use the command

```
qemu-system-x86_64 -cdrom minux.iso
```

to run the OS.