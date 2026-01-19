#ifndef SCREEN_H
#define SCREEN_H

void clear_screen(void);
void clear_default_cursor(void);
void print(const char *str, unsigned char color);
void print_(const char *str, unsigned char color, int x, int y);


#endif