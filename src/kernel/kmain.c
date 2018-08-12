
#include <vga/vga.h>
#include <util/multiboot.h>
#include <std/types.h>
#include <terminal/terminal.h>
#include <cpu/irq.h>
#include <error/kernel_errors.h>
#include <irq_handlers/timer.h>
#include <util/multiboot.h>

int kmain(struct multiboot_tag *tag){
    load_IDT();
    register_errors();
    init_pit();
    set_background(VGA_CYAN);
    set_foreground(VGA_WHITE);
    clr();
    kprintf("Minux OS - Ver. %d by Anish Basu\n", 1);
    sleep(2);
    set_background(VGA_BLACK);
    set_foreground(VGA_LIGHT_GRAY);
    clr();
    struct multiboot_tag_mmap* mmap_tag =  mb_get_mmap_tag(tag);
    
    int entries = num_mmap_entries(mmap_tag);
    for(int i = 0; i < entries; i++){
        multiboot_memory_map_t* mmap_entry = get_mmap_entry(mmap_tag, i);
        kprintf("Addr: %x Size: %dB Type: %d Zero: %d\n", mmap_entry->addr, mmap_entry->len, mmap_entry->type, mmap_entry->zero);
    }
    //struct multiboot_tag_basic_meminfo *meminfo_tag = (struct multiboot_tag_basic_meminfo *) get_tag_by_type(tag, MULTIBOOT_TAG_TYPE_BASIC_MEMINFO);
    //kprintf("mem_lower = %dKB\nmem_upper = %dKB\n", meminfo_tag->mem_lower, meminfo_tag->mem_upper);
    //kprintf("Magic Number: %d\n", multiboot_magic == MULTIBOOT_BOOTLOADER_MAGIC);
    while(1);
    return 0;
}