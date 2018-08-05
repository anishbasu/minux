#include <cpu/irq.h>
#include <std/types.h>
#include <util/io.h>
#include <cpu/register.h>
#include <cpu/spinlock.h>
#include <terminal/terminal.h>
#include <std/string.h>
//Graciously taken from: https://github.com/tmathmeyer/sos/blob/master/src/pic/interrupts.c
// and https://wiki.osdev.org/Interrupt_Descriptor_Table
// and http://www.flingos.co.uk/docs/reference/IRQs/

//Interrupts
IDTDesc_t IDT[NUM_INTERRUPTS];

//Store the registered handlers
void (* handlers[NUM_INTERRUPTS]) (struct InterruptFrame *);

//Put all the function pointers in a label for init
void (* IRQS[NUM_INTERRUPTS]) (void) = {
    &irq_0, &irq_1, &irq_2 ,&irq_3, &irq_4, &irq_5, &irq_6, &irq_7,
    &irq_8, &irq_9, &irq_10,&irq_11,&irq_12,&irq_13,&irq_14,&irq_15,
    &irq_16,&irq_17,&irq_18,&irq_19,&irq_20,&irq_21,&irq_22,&irq_23,
    &irq_24,&irq_25,&irq_26,&irq_27,&irq_28,&irq_29,&irq_30,&irq_31,
    &irq_32,&irq_33,&irq_34,&irq_35,&irq_36,&irq_37,&irq_38,&irq_39,
    &irq_40,&irq_41,&irq_42,&irq_43,&irq_44,&irq_45,&irq_46,&irq_47,
    &irq_48,&irq_49,&irq_50,&irq_51,&irq_52,&irq_53,&irq_54,&irq_55,
    &irq_56,&irq_57,&irq_58,&irq_59,&irq_60,&irq_61,&irq_62,&irq_63,
    &irq_64
};
//Router that handles all interrupts
//TODO: break up into Top and Bottom Half
spinlock_t interrupt_lock;
void interrupt_router(uint64_t id, uint64_t stack) {
    if(try_lock(&interrupt_lock)){
        if (handlers[id]) { //If a handler is available, call it
            handlers[id](get_frame(stack, id));
            //Additional Error Handling code needed
        } // Dump stack else (NEED PANIC FUNCTION)

        //Send End of Interrupt (EOI) Sugnal
        if (id < IRQ_BASE + 16) {
            //Slave
            if (id >= IRQ_BASE + 8 )
                outb(PIC_SLAVE, PIC_EOI);
            //Master
            if (id >= IRQ_BASE)
                outb(PIC_MASTER, PIC_EOI);
        }
        spin_unlock(&interrupt_lock);
    }
}
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

    // Disable all IRQs in IMR (Interrupt Mask Register) to add the IDT
    outb(PIC_MASTER_DATA, 0xFF);
    outb(PIC_SLAVE_DATA,  0xFF);

    uint16_t code_seg = cs();
    for(size_t i = 0; i < NUM_INTERRUPTS; i++) {
        IDT[i] = create_IDTDesc(code_seg, (uintptr_t) IRQS[i]);
    }
    //Set the IDT Entries
    IDTPointer_t pointer = {
        .base = IDT,
        .limit = sizeof(IDT) - 1
    }; 
    asm("lidt %0" : : "m" (pointer)); // Load the IDT
    asm("sti");//Set the IDT Entry
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
void set_interrupt_handler(int handler_id, void (* func) (struct InterruptFrame *)) {
    handlers[handler_id] = func;
}

void disable_irq_line(uint16_t irq_line){
    irq_line = IRQ_BASE_LINE(irq_line);
    uint16_t port;
    if (irq_line < 8) {
        port = PIC_MASTER_DATA;
    } else {
        port = PIC_SLAVE_DATA;
        irq_line -= 8; // Offset the value for setting the slave only
    }
    //Set the flag bit on the mask
    uint8_t mask = inb(port) | (1 << irq_line);
    print_num(mask, 16);
    //Set the flags on the PIC
    outb(port, mask);
}

void enable_irq_line(uint16_t irq_line) {
    irq_line = IRQ_BASE_LINE(irq_line);
    uint16_t port;
    if (irq_line < 8) {
        port = PIC_MASTER_DATA;
    } else {
        port = PIC_SLAVE_DATA;
        irq_line -= 8; // Offset the value for setting the slave only
    }
    //Unset the flag bit on the mask
    uint8_t mask = inb(port) & ~(1 << irq_line); //Set the zero flag on the irq_line-th bit
    //Set the flags on the PIC
    outb(port, mask);
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