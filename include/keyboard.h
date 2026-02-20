#ifndef KEYBOARD_H
#define KEYBOARD_H


#include "../lib/h/io.h"
#include "../lib/h/types.h"
#include "pic.h"
#include "screen.h"
#include "var.h"
#include "shell.h"

void keyboard_handler(void);
void keyboard_init(void);

#endif