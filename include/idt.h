#ifndef IDT_H
#define IDT_H

#include "../lib/h/types.h"

struct idt_entry
{
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
} __attribute__((packed));

struct idtr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

extern struct idt_entry idt[256];
extern struct idtr idtr;

void idt_set_gate(uint8_t num, uint32_t handler, uint16_t selector, uint8_t flags);
void idt_init(void);


#endif