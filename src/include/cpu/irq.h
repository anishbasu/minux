#ifndef IRQ_H
#define IRQ_H
#include <std/types.h>

#define PIC_MASTER 0x20
#define PIC_SLAVE  0xA0
#define PIC_MASTER_DATA (PIC_MASTER + 1)
#define PIC_SLAVE_DATA  (PIC_SLAVE  + 1)
#define PIC_EOI    0x20 //End of interrupt
#define IRQ_BASE   0x20


#define NUM_INTERRUPTS 256

/**
 * IDT Entry Structure
 */
typedef struct IDTDescOpts {
    uint8_t stack_ok  : 3;
    uint8_t zeros     : 5;
    uint8_t gate_type : 1;
    uint8_t ones      : 3;
    uint8_t zero      : 1;
    uint8_t DPL       : 2;
    uint8_t present   : 1;
}__attribute__((packed)) IDTDescOpts_t;

typedef struct IDTDesc {
    uint16_t offset_l; // 0 .. 15 offset bits
    uint16_t selector; // a code segment selector in GDT or LDT
    IDTDescOpts_t opts;     // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
    uint8_t  type_attr;// type and attributes
    uint16_t offset_m; // 16 .. 31 offset bits
    uint32_t offset_h; // 32 .. 63 offset bits
    uint32_t reserved; // reserved
} __attribute__((packed)) IDTDesc_t;


/**
 * IDT Pointer
 */
typedef struct IDTPointer {
    uint16_t limit;
    uintptr_t base;
} __attribute__((packed)) IDTPointer_t;

/**
 * Actual Interrupt
 */
typedef struct InterruptFrame{
   uintptr_t instr_ptr, code_segment;
   uint64_t  cpu_flags;
   uintptr_t stack_ptr;
   uint64_t  stack_segment;
} __attribute__((packed));


//Defined in idt.c
void load_IDT();
IDTDesc_t create_IDTDesc(uint16_t gdt_selector, uintptr_t fn_ptr);
void set_interrupt_handler(int handler_id, void (* func) (struct InterruptFrame));
uint64_t get_error_code(struct InterruptFrame *);
struct InterruptFrame* get_frame(uintptr_t frame_ptr, uint64_t id);
//Defined in src/asm/idt.asm
extern void irq_0(void);
extern void irq_1(void);
extern void irq_2(void);
extern void irq_3(void);
extern void irq_4(void);
extern void irq_5(void);
extern void irq_6(void);
extern void irq_7(void);
extern void irq_8(void);
extern void irq_9(void);
extern void irq_10(void);
extern void irq_11(void);
extern void irq_12(void);
extern void irq_13(void);
extern void irq_14(void);
extern void irq_15(void);
extern void irq_16(void);
extern void irq_17(void);
extern void irq_18(void);
extern void irq_19(void);
extern void irq_20(void);
extern void irq_21(void);
extern void irq_22(void);
extern void irq_23(void);
extern void irq_24(void);
extern void irq_25(void);
extern void irq_26(void);
extern void irq_27(void);
extern void irq_28(void);
extern void irq_29(void);
extern void irq_30(void);
extern void irq_31(void);
extern void irq_32(void);
extern void irq_33(void);
#endif