#include "../include/shell.h"


void showShell(int isNew)
{
    if (isNew) {
        clear_screen();
        print_("-> $ ", 0x0A, 0, 0);
        basic_cursor();

        yCursorShell = 0;
        xCursorShell = 6;
        
        cursor_to(xCursorShell, yCursorShell);
    }
}