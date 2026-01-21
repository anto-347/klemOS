#include "../lib/h/types.h"
#include "../include/idt.h"

void idt_set_gate(uint8_t num, uint32_t handler, uint16_t selector, uint8_t flags)
{
    idt[num].offset_high = (handler >> 16) & 0xFFFF;
    idt[num].offset_low = handler & 0xFFFF;
    idt[num].selector = selector;
    idt[num].type_attr = flags;
    idt[num].zero = 0;
}

extern void idt_load(uint32_t);

void init_idt(void)
{
    idtr.base = (uint32_t)&idt;
    idtr.limit = (sizeof(struct idt_entry) * 256) - 1;

    for (int i = 0; i < 256; i++) {
        idt[i].offset_high = 0;
        idt[i].offset_low = 0;
        idt[i].selector = 0;
        idt[i].type_attr = 0;
        idt[i].zero = 0;
    }

    idt_load((uint32_t)&idt);
}