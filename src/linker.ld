ENTRY(start)

SECTIONS {
    . = 1M;

    .boot :
    {
        /* Header first (duh) */
        KEEP(*(.multiboot_header))
    }
    
    .text :
    {
        /*Boot file*/
        *(.text)
    }
}