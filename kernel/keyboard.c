#include "../include/keyboard.h"



static char scancode_to_ascii_min[] = {
    0, 0, '&', 0, '"', '\'', '(', '-', 0, '_', 0, 0, ')', '=', 'B',
    0, 'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 0, '$', 'E',
    0, 'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', '%', '*',
    'M', '<', 'w', 'x', 'c', 'v', 'b', 'n', ',', ';', ':', '!', 0,
    0, 0, ' '
};

static char scancode_to_ascii_maj[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 0, '+', 'b',
    0, 'A', 'Z', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', 0, 0, 'e',
    0, 'Q', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', '%', '*',
    'm', '>', 'W', 'X', 'C', 'V', 'B', 'N', '?', '.', '/', '!', 'm',
    0, 0, ' '
};


void keyboard_handler(void)
{
    uint8_t scancode = inb(0x60);

    char selecteurMaj;
    char selecteurEntree;
    char selecteurBackspace;

    if (scancode & 0x80 )
    {
        pic_send_eoi(1);
        return;
    }

    char ascii = 0;
    if (isMajOn) {
        if (scancode < sizeof(scancode_to_ascii_maj)) {
            ascii = scancode_to_ascii_maj[scancode];
        } else {
            pic_send_eoi(1);
            return;
        }
    } else {
        if (scancode < sizeof(scancode_to_ascii_min)) {
            ascii = scancode_to_ascii_min[scancode];
        } else {
            pic_send_eoi(1);
            return;
        }
    }

    if (!menuPassed && scancode == 0x1C) {
        showShell(1);
        menuPassed = 1;
    } else if (!menuPassed && scancode != 0x1C) {
        pic_send_eoi(1);
        return;
    } else {
        if (isMajOn) {
            selecteurMaj = 'm';
            selecteurEntree = 'e';
            selecteurBackspace = 'b';
        } else {
            selecteurMaj = 'M';
            selecteurEntree = 'E';
            selecteurBackspace = 'B';
        }

        if (ascii == 0) {
            pic_send_eoi(1);
            return;
        }

        if (ascii == selecteurBackspace) {
            backspace();
            return;
        } else if (ascii == selecteurMaj) {
            isMajOn ^= 1;
        } else if (ascii == selecteurEntree) {
            entree_keyboard(ascii);
        } else {
            print_from_keyboard(ascii);
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