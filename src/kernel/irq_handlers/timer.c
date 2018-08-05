#include <util/io.h>
#include <cpu/irq.h>
#include <terminal/terminal.h>
#include <irq_handlers/timer.h>
int tick = 0;
uint16_t read_pit_count(uint8_t channel) {
    pit_command_t command = { 
        .fields = { 
            .channel = 0,
            .access_mode = false,
            .operating_mode = OP_INT_ON_TERMINAL_COUNT,
            .bcd_mode = false
        }
    };
    outb(PIT_COMMAND_CHANNEL, command.bits);
    uint16_t count = inb(PIT_CHANNEL(0)); //Low Byte
    count = count | (inb(PIT_CHANNEL(0)) << 8); //High Byte
    return count;
}

void set_pit_phase(int hz) {
    pit_command_t command = {
        .fields = {
            .channel = 0,
            .access_mode = ACCESS_HI_BYTE | ACCESS_LO_BYTE,
            .operating_mode = OP_RATE_GEN,
            .bcd_mode = true
        }
    };
    outb(PIT_COMMAND_CHANNEL, command.bits);
    uint16_t div = PIT_MAX_FREQ / hz;
    outb(PIT_CHANNEL(0), div & 0xFF);
    outb(PIT_CHANNEL(0), div >> 8);
}

void test_func(struct InterruptFrame* frame){
    kprintf("Tick: %d\n", tick);
    tick++;
}
void init_pit() {
    set_pit_phase(20);
    set_interrupt_handler(IRQ_LINE(0), &test_func);
    enable_irq_line(IRQ_LINE(0));
}

