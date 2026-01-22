#include "../include/screen.h"
#include "../include/load.h"
#include "../include/idt.h"


void main(void)
{
    prepare_screen();
    idt_init();

    asm volatile ("sti");

    while(1)
    {
        asm volatile ("hlt");
    }
}