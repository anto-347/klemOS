#include "../include/keyboard.h"
#include "../include/pic.h"
#include "../lib/h/io.h"

void keyboard_handler(void)
{
    uint8_t scancode = inb(0x60);

    char *video = (char*) 0xB8000;
    static int pos = 0;

    if (pos >= 80 * 25)
    {
        pos = 0;
    }

    video[pos * 2] = 'X';
    video[pos * 2 + 1] = 0x0F;
    pos++;
}

void keyboard_init(void)
{
    
}