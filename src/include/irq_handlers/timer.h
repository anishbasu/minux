#ifndef TIMER_H
#define TIMER_H
#include <std/types.h>

#define PIT_CHANNEL(mode) (0x40 + mode)
#define PIT_COMMAND_CHANNEL 0x43
//-- Access Mode (Can Combine)
#define ACCESS_LO_BYTE 1
#define ACCESS_HI_BYTE 2
//-- Operating Mode
#define OP_INT_ON_TERMINAL_COUNT         0
#define OP_HARDWR_RETRIGGERABLE_ONE_SHOT 1
#define OP_RATE_GEN                      2
#define OP_SQUARE_WAVE                   3
#define OP_SOFTWR_TRIG_STROBE            4
#define OP_HARDWR_TRIG_STROBE            5
// PIT Max Frequency
#define PIT_MAX_FREQ 1193180

//Unions to the rescue: https://stackoverflow.com/questions/11903820/casting-struct-into-int
typedef union pid_command {
    struct {
        bool bcd_mode          : 1;
        uint8_t operating_mode : 3;
        uint8_t access_mode    : 2;
        uint8_t channel        : 2;
    } __attribute__((packed)) fields;
    uint8_t bits; 
} pit_command_t;

uint16_t read_pit_count(uint8_t channel);
void set_pit_phase(int hz);
void init_pit();
void test_func(struct InterruptFrame* frame);
#endif