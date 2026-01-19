#include "../include/screen.h"

void main(void)
{
    clear_screen();

    char *video = (char*) 0xb8000;
    *video = 'Y';
    *(video + 1) = 0x0F;
    
    *(video + 2) = 'o';
    *(video + 3) = 0x0F;

    while(1);
}