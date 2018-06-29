ENTRY(start)

SECTIONS {
    . = 1M;

    .boot :
    {
        /* Header first (duh) */
        *(.multiboot_header)
    }
    
    .text :
    {
        /*Boot file*/
        *(.text)
    }
}