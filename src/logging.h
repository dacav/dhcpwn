#ifndef _DHCPWN_LOGGING_H
#define _DHCPWN_LOGGING_H

#include <stdio.h>

void log_setstream(FILE *stream);

void info(const char *fmt, ...);

#endif
