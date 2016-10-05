#include "rogue.h"
#include "util.h"

#include <stdlib.h>
#include <string.h>

struct rogue {
    uint8_t *macaddr;
    size_t maclen;
};

rogue_t rogue_new_ethrnd()
{
    return rogue_new(NULL, 6 /* Ethernet mac len */);
}

rogue_t rogue_new(const uint8_t *macaddr, size_t maclen)
{
    rogue_t out = malloc(sizeof(struct rogue));
    if (out == NULL) goto fail;

    out->macaddr = calloc(maclen, sizeof(uint8_t));
    if (out->macaddr == NULL) goto fail;
    if (macaddr != NULL) {
        memcpy(out->macaddr, macaddr, maclen);
    } else {
        random_bytes(out->macaddr, maclen);
    }
    return out;

  fail:
    rogue_del(out);
    return NULL;
}

void rogue_del(rogue_t r)
{
    if (r == NULL) return;
    if (r->macaddr != NULL) free(r->macaddr);
    free(r);
}
