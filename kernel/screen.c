#include "../include/screen.h"


#define VIDEO_MEMORY 0xb8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25


void clear_screen(void)
{
    char *video_memory = (char*) 0xb8000;
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT * 2; i += 2) {
        video_memory[i] = ' ';
        video_memory[i + 1] = 0x07;
    }
}

void clear_default_cursor(void)
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void print(const char *str, unsigned char color)
{
    print_(str, color, 0, 0);
}

void print_(const char *str, unsigned char color, int x, int y)
{
    char *video = (char*) VIDEO_MEMORY;
    int offset = (y * SCREEN_WIDTH + x) * 2;
    int i = 0;

    while (str[i] != '\0') {
        video[offset + i * 2] = str[i];
        video[offset + i * 2 + 1] = color;
        i++;
    }
}

void basic_cursor(void)
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x0D);
    outb(0x3D4, 0x0B);
    outb(0x3D5, 0x0E);
}

void cursor_to(int x, int y)
{
    uint8_t pos = y * 80 + x;

    outb(0x3D4, 0x0E);
    outb(0x3D5, (pos >> 8) & 0xFF);

    outb(0x3D4, 0x0F);
    outb(0x3D5, pos & 0xFF);
}

void backspace(void)
{
    char str = ' ';
    print_(&str, 0x0F, xCursorShell, yCursorShell);

    idxIptUser--;
    iptUser[idxIptUser] = ' ';
    xCursorShell--;

    if (xCursorShell < 0) {
        yCursorShell --;
        xCursorShell = 80;
    }

    cursor_to(xCursorShell, yCursorShell);

    pic_send_eoi(1);
}

void print_from_keyboard(char ascii)
{
    char str[2];
    str[0] = ascii;
    str[1] = '\0';
    iptUser[idxIptUser] = *str;
    idxIptUser++;

    print_(str, 0x0F, xCursorShell, yCursorShell);
    xCursorShell++;
    if (xCursorShell >= 80) {
        xCursorShell = 0;
        yCursorShell++;
    }

    cursor_to(xCursorShell, yCursorShell);
}