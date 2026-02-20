#ifndef SCREEN_H
#define SCREEN_H

#include "var.h"
#include "../lib/h/io.h"
#include "pic.h"

void clear_screen(void);
void clear_default_cursor(void);
void print(const char *str, unsigned char color);
void print_(const char *str, unsigned char color, int x, int y);
void basic_cursor(void);
void cursor_to(int x, int y);
void backspace(void);
void print_from_keyboard(char ascii);


#endif