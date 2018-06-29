ld = ~/opt/cross/bin/x86_64-elf-ld
all:
	nasm -f elf64 ./src/multiboot_header.asm -o ./build/multiboot_header
	nasm -f elf64 ./src/boot.asm -o ./build/boot
	cp -r ./src/isofiles ./build
	cd ./build && $(ld) --nmagic -o ./isofiles/boot/kernel.bin -T ../src/linker.ld multiboot_header boot
	cd ./build && grub-mkrescue --verbose isofiles -o os.iso
clean:
	rm -rf ./build/*