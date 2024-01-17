#include "version.h"

void print::version(void) noexcept{
    printf ("Version: %s%s%s\n", COLOR_GREEN, PROGRAME_VERSION, COLOR_RESET);
}
