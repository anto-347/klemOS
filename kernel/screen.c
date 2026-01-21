#include "../include/screen.h"
#include "../lib/h/io.h"


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

void print(const char *str, unsigned char color) {
    print_(str, color, 0, 0);
}

void print_(const char *str, unsigned char color, int x, int y) {
    char *video = (char*) VIDEO_MEMORY;
    int offset = (y * SCREEN_WIDTH + x) * 2;
    int i = 0;

    while (str[i] != '\0') {
        video[offset + i * 2] = str[i];
        video[offset + i * 2 + 1] = color;
        i++;
    }
}