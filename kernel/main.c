#include "../include/screen.h"
#include "../include/load.h"
#include "../include/idt.h"


void main(void)
{
    prepare_screen();

    char *video = (char*) 0xB8000;
    video[0] = 'T';
    video[1] = 0x0F;
    video[2] = 'E';
    video[3] = 0x0F;
    video[4] = 'S';
    video[5] = 0x0F;
    video[6] = 'T';
    video[7] = 0x0F;

    idt_init();

    video[8] = '2';
    video[9] = 0x0F;
    asm volatile ("sti");

    while(1)
    {
        asm volatile ("hlt");
    }
}