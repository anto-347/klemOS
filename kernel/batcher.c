#include "../include/batcher.h"


void clear_batcher(void)
{
    for (int i = 0; i < 256; i++) {
        iptUser[i] = ' ';
    }
    idxIptUser = 0;
}