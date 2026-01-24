#include "../include/keyboard.h"
#include "../include/pic.h"
#include "../lib/h/io.h"
#include "../lib/h/types.h"
#include "../include/screen.h"
#include "../include/var.h"


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
        if (menuPassed)
        {
            print_("oui", 0x0F, 50, 20);
        }
        else
        {
            print_("non", 0x0F, 50, 20);
        }
    } 
    else
    {
        pic_send_eoi(1);
        return;
    }

    if (!menuPassed && scancode == 0x1C)
    {
        // montrer terminal
        menuPassed == 1;
    }
    else if (!menuPassed && scancode != 0x1C)
    {
        pic_send_eoi(1);
        return;
    }
    else
    {
        if (ascii != 0) {
            static int x = 0;
            static int y = 0;
    
            char str[2];
            str[0] = ascii;
            str[1] = '\0';
    
            print_(str, 0x0F, x, y);
    
            x++;
            if (x >= 79) {
                x = 0;
                y++;
            }
        }
    }

    pic_send_eoi(1);
}

void keyboard_init(void)
{
    
}