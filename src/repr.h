#ifndef _DHCPWN_REPR_H
#define _DHCPWN_REPR_H

#include <stdint.h>
#include <stdlib.h>

/* The functions declared in this module are not good for secure string
 * handling. No check is done for buffer sizes. They are meant for
 * internal use only. */

/* Represent an array of bytes as string.
 *
 * Returns a newly allocated string which should be released with a
 * free. Returns NULL if malloc gave NULL.
 */
char * repr_bytes(
    const uint8_t *bytes,
    size_t len,
    const char *sep,
    const char *prefix,
    const char *suffix
);


#endif
