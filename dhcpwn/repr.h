#ifndef _DHCPWN_REPR_H
#define _DHCPWN_REPR_H

#include <stdint.h>
#include <stdlib.h>

/* The functions declared in this module handle strings.
 *
 * General assumptions:
 * - The caller has ownership on the input and output items.
 * - The caller ensures that strings are null-terminated
 */

/* Represent an array of bytes as string.
 *
 * Returns NULL on faliure.
 * Returns a newly allocated string which should be released with a
 * free.
 */
char * repr_bytes(
    const uint8_t *bytes,
    size_t len,
    const char *sep,
    const char *prefix,
    const char *suffix
);

/* Like sprintf, but on a new char sequence.
 *
 * Returns NULL on failure.
 * Returns a newly allocated string which should be released with a free.
 */
char * repr_printf(const char *fmt, ...);

#endif
