#include "../include/load.h"
#include "../include/screen.h"

void prepare_screen(void)
{
    clear_screen();
    clear_default_cursor();

    print_("Chargement...", 0x0F, 30, 0);
    print_("klemOS", 0x0F, 30, 2);
}