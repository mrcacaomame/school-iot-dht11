#include "help.h"

void print::help(void) noexcept{
    printf ("%s help options ...\n", PROGRAME_NAME);

    printf ("[ %-3s | %-20s ]: Output the programe version.\n", "-v", "--version");
    printf ("[ %-3s | %-20s ]: Output the programe options.\n", "-h", "--help");
    printf ("[ %-3s | %-20s ]: Set the config file path.\n", "-c", "--config");
    printf ("[ %-3s | %-20s ]: Create config file.\n", "-cc", "--create-config");
    
}