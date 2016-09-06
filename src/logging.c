#include <stdarg.h>

#include "logging.h"

FILE * LOG_FILE = NULL;

void log_setstream(FILE *stream)
{
    LOG_FILE = stream;
}

void log_info(const char *fmt, ...)
{
    if (LOG_FILE == NULL) return;

    va_list ap;
    va_start(ap, fmt);
    vfprintf(LOG_FILE, fmt, ap);
    va_end(ap);
}
