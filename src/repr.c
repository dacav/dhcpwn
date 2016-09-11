#include "repr.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "logging.h"

char * repr_bytes(const uint8_t *bytes, size_t len, const char *sep,
                  const char *prefix, const char *suffix)
{
    const size_t seplen    = sep == NULL    ? 0 : strlen(sep);
    const size_t prefixlen = prefix == NULL ? 0 : strlen(prefix);
    const size_t suffixlen = suffix == NULL ? 0 : strlen(suffix);

    const size_t size =
        prefixlen
        + (2 * len)          /* Two hex digit per byte */
        + seplen * (len - 1) /* Between each pair of bytes */
        + suffixlen
        + 1                  /* Terminating '0' */
    ;

    char *out = malloc(size);
    if (out == NULL) return NULL;

    out[size - 1] = '\0';

    unsigned offset = 0;
    if (prefix)
        offset += sprintf(out + offset, "%s", prefix);

    if (len > 0) {
        offset += sprintf(out + offset, "%02x", bytes[0]);
        for (unsigned i = 1; i < len; i ++) {
            if (sep)
                offset += sprintf(out + offset, "%s", sep);
            offset += sprintf(out + offset, "%02x", bytes[i]);
        }
    }

    if (suffix)
        offset += sprintf(out + offset, "%s", suffix);

    assert(offset + 1 == size);
    assert(out[offset] == '\0');
    return out;
}
