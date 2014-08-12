#include <stdio.h>
#include <stdarg.h>

#include "log.h"

int printlogf( const char* format, ... ) {
    va_list args;
    va_start( args, format );
    vfprintf( stderr, format, args );
    va_end( args );
    return 0;
}