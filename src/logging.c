#include <stdarg.h>

#include "logging.h"

FILE * LOG_FILE = NULL;
log_level_t LEVEL = LOG_INFO;

void log_setup(FILE *stream, log_level_t level)
{
    LOG_FILE = stream;
    LEVEL = level;
}

static void log_core(const char *fmt, va_list args)
{
    if (LOG_FILE == NULL) return;
    vfprintf(LOG_FILE, fmt, args);
}

void log_debug(const char *fmt, ...)
{
    if (LEVEL > LOG_DEBUG) return;

    va_list ap;
    va_start(ap, fmt);
    log_core(fmt, ap);
    va_end(ap);
}

void log_info(const char *fmt, ...)
{
    if (LEVEL > LOG_INFO) return;

    va_list ap;
    va_start(ap, fmt);
    log_core(fmt, ap);
    va_end(ap);
}
