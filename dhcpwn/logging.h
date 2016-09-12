#ifndef _DHCPWN_LOGGING_H
#define _DHCPWN_LOGGING_H

#include <stdio.h>

typedef enum {
    LOG_DEBUG = 1,
    LOG_INFO = 2,
    LOG_ERROR = 3,
} log_level_t;

void log_setup(FILE *stream, log_level_t level);

void log_debug(const char *fmt, ...);
void log_info(const char *fmt, ...);
void log_error(const char *fmt, ...);

#endif
