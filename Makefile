ld := ~/opt/cross/bin/x86_64-elf-ld
testflags = -Wno-unused-parameter -Wno-unused-variable -Wno-div-by-zero
cflags := -nostdlib -nostdinc -fno-stack-protector -Wall -Wextra -Werror $(testflags) -Isrc/include -m64 -s -c
build_path := build
src_path := src

c_src_path := src/kernel
c_sources := $(shell find $(c_src_path) -name '*.c')
c_objs    := $(patsubst $(c_src_path)/%.c, $(build_path)/%.o, $(c_sources))

asm_sources := $(shell find $(src_path) -name '*.asm')
asm_objs    := $(patsubst $(src_path)/%.asm, $(build_path)/%.elf, $(asm_sources))

all: make_dir asm_build c_build
	cp -r ./src/isofiles ./build
	$(ld) --nmagic -o build/isofiles/boot/kernel.bin -T ./src/linker.ld $(asm_objs) $(c_objs)
	grub-mkrescue ./build/isofiles -o minux.iso

make_dir:
	mkdir -p build

asm_build: $(asm_objs)

c_build: $(c_objs)

$(build_path)/%.o: $(c_src_path)/%.c
	mkdir -p $(dir $@)
	gcc $(cflags) $< -I$(c_src_path) -o $@

$(build_path)/%.elf: $(src_path)/%.asm
	mkdir -p $(dir $@)
	nasm -f elf64 $< -o $@

clean:
	rm -rf ./build
