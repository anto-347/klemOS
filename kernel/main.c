void main()
{
    char* video = (char*) 0xb8000;
    *video = 'H';
    *(video + 1) = 0x0F;
    
    while(1);
}