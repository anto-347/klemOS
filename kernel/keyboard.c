#include "../include/keyboard.h"



static char scancode_to_ascii[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 'B',
    0, 'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', '%', '*',
    'M', '\\', 'w', 'x', 'c', 'v', 'b', 'n', ',', ';', ':', '!', 0,
    '*', 0, ' '
};


static char min_chars[] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

static char maj_chars[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
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
        if (ascii == 0) {
            pic_send_eoi(1);
            return;
        }

        if (ascii == 'B') {
            backspace();
            return;
        }

        print_from_keyboard(ascii);
    }

    pic_send_eoi(1);
}

void keyboard_init(void)
{
    for (int i = 0; i < 256; i++) {
        iptUser[i] = ' ';
    }
}