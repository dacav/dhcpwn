#ifndef _DHCPWN_ROGUE_H
#define _DHCPWN_ROGUE_H

#include <stdint.h>
#include <stdlib.h>

typedef struct rogue * rogue_t;

rogue_t rogue_new_ethrnd();
rogue_t rogue_new(const uint8_t *macaddr, size_t maclen);
void rogue_del(rogue_t);
const char * rogue_tostr(rogue_t);

#endif // _DHCPWN_ROGUE_H
