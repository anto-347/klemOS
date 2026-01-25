#include "../include/keyboard.h"


static char scancode_to_ascii[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0,
    0, 'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', '%', '*',
    0, '\\', 'w', 'x', 'c', 'v', 'b', 'n', ',', ';', ':', '!', 0,
    '*', 0, ' '
};

void keyboard_handler(void)
{
    uint8_t scancode = inb(0x60);

    if (scancode & 0x80 )
    {
        pic_send_eoi(1);
        return;
    }

    char ascii = 0;
    if (scancode < sizeof(scancode_to_ascii))
    {
        ascii = scancode_to_ascii[scancode];
    } 
    else
    {
        pic_send_eoi(1);
        return;
    }

    if (!menuPassed && scancode == 0x1C)
    {
        showShell(1);
        menuPassed = 1;
    }
    else if (!menuPassed && scancode != 0x1C)
    {
        pic_send_eoi(1);
        return;
    }
    else
    {
        if (ascii != 0) {    
            char str[2];
            str[0] = ascii;
            str[1] = '\0';
    
            print_(str, 0x0F, xCursorShell, yCursorShell);
    
            xCursorShell++;
            if (xCursorShell >= 80) {
                xCursorShell = 0;
                yCursorShell++;
            }
            cursor_to(xCursorShell, yCursorShell);
        }
    }

    pic_send_eoi(1);
}

void keyboard_init(void)
{
    for (int i = 0; i < 256; i++) {
        iptUser[i] = ' ';
    }
}