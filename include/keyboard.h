#ifndef KEYBOARD_H
#define KEYBOARD_H


#include "../include/pic.h"
#include "../lib/h/io.h"
#include "../lib/h/types.h"
#include "../include/screen.h"
#include "../include/var.h"
#include "../include/shell.h"

void keyboard_handler(void);
void keyboard_init(void);

#endif