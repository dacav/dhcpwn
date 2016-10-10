#ifndef _DHCPWN_OPTS_H
#define _DHCPWN_OPTS_H


#ifdef DHCPWN_SETUP
#   define OPT(type, name, dflt) type name = dflt
#else
#   define OPT(type, name, dflt) extern type name
#endif

#include <stdint.h>

OPT(char *,     DHCPWN_Interface,   "eth0");
OPT(uint16_t,   DHCPWN_InboundPort, 52);
OPT(unsigned,   DHCPWN_RandomSeed,  0);     // 0 -> randomize

#endif // _DHCPWN_OPTS_H
