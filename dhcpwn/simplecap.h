#ifndef _DHCPWN_SPCAP_H
#define _DHCPWN_SPCAP_H

#include <pcap.h>

pcap_t * spcap_new(const char *device);

#endif
