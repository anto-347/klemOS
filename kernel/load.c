#include "../include/load.h"
#include "../include/screen.h"

void prepare_screen(void)
{
    clear_screen();
    clear_default_cursor();

    print_("Bienvenue sur klemOS", 0x0F, 20, 0);
    print_("Appuiez sur Entree pour continuer", 0x0F, 20, 2);
}