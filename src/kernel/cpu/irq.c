#include <cpu/irq.h>
#include <std/types.h>
#include <util/io.h>
#include <cpu/register.h>
//Graciously taken from: https://github.com/tmathmeyer/sos/blob/master/src/pic/interrupts.c
// and https://wiki.osdev.org/Interrupt_Descriptor_Table
// and http://www.flingos.co.uk/docs/reference/IRQs/

IDTDesc_t IDT[NUM_INTERRUPTS];

//Store the registered handlers
void (* handlers[NUM_INTERRUPTS]) (struct InterruptFrame_t *);

//Put all the function pointers in a label for init
void (* IRQS[NUM_INTERRUPTS]) (void) = {
    &irq_0, &irq_1, &irq_2 ,&irq_3, &irq_4, &irq_5, &irq_6, &irq_7,
    &irq_8, &irq_9, &irq_10,&irq_11,&irq_12,&irq_13,&irq_14,&irq_15,
    &irq_16,&irq_17,&irq_18,&irq_19,&irq_20,&irq_21,&irq_22,&irq_23,
    &irq_24,&irq_25,&irq_26,&irq_27,&irq_28,&irq_29,&irq_30,&irq_31,
    &irq_32,&irq_33
};

void load_IDT(){
    //Notify the PIC that we're adding IDT Entries
    //INIT command ICW1 + ICW4
    outb(PIC_MASTER, 0x11);
    outb(PIC_SLAVE, 0x11);

    //Set Base Numbers for each PIC
    outb(PIC_MASTER_DATA, IRQ_BASE); //PIC 1 interrupts from 0x20
    outb(PIC_SLAVE_DATA,  IRQ_BASE + 8);//PIC 2 interrupts from 0x28

    outb(PIC_MASTER_DATA, 0x04); // Set PIC 1 as Master
    outb(PIC_SLAVE_DATA,  0x02); // Set PIC 2 as Slave

    // Set x86 mode code for 8259 PIC chips
    outb(PIC_MASTER_DATA, 0x01); 
    outb(PIC_SLAVE_DATA,  0x01);

    // Mask all IRQs to add the IDT
    outb(PIC_MASTER_DATA, 0x00);
    outb(PIC_SLAVE_DATA,  0x00);

    for(size_t i; i < NUM_INTERRUPTS; i++) {
        IDT[i] = create_IDTDesc(cs(), (uintptr_t) IRQS[i]);
    }
    //Set the IDT Entries
    IDTPointer_t pointer = {
        .base = IDT,
        .limit = sizeof(IDT) - 1
    }; 
    asm("lidt %0" : : "m" (pointer));

    asm("sti"); //Set the IDT Entry
}

IDTDesc_t create_IDTDesc(uint16_t gdt_selector, uintptr_t fn_ptr) {
    IDTDesc_t desc;
    desc.selector = gdt_selector;
    desc.offset_l = (uint16_t)fn_ptr;
    desc.offset_m = (uint16_t)(fn_ptr >> 16);
    desc.offset_h = (uint32_t)(fn_ptr >> 32);

    desc.opts.stack_ok = 0;
    desc.opts.present  = 1;
    desc.opts.DPL      = 3;
    desc.opts.gate_type= 1;
    desc.opts.ones     = 7;
    desc.opts.zero     = 0;
    desc.opts.zeros    = 0;

    desc.reserved = 0;
    return desc;
}
void set_interrupt_handler(int handler_id, void (* func) (struct InterruptFrame)) {
    handlers[handler_id] = func;
}

struct InterruptFrame* get_frame(uintptr_t frame_ptr, uint64_t id) {
    switch(id) { //Fault IRQ IDs
        case 8:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 17:
        case 30:
            frame_ptr += sizeof(uint64_t); // Error code should've been here (retrieve using get_error_code)
    }
    struct InterruptFrame *actual_frame = (struct InterruptFrame *) frame_ptr;

    return actual_frame + 3;
}

uint64_t get_error_code(struct InterruptFrame *frame) {
    uintptr_t *framew = (uintptr_t *) frame;
    return framew[-1];
}