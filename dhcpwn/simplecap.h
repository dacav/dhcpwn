#ifndef _DHCPWN_SPCAP_H
#define _DHCPWN_SPCAP_H

#include <pcap.h>
#include <stdint.h>

/* Create a pcap handler, use application specific settings (e.g. promisc mode).
 *
 * Param device: the choosen network device;
 * Returns NULL on error, error message is logged;
 * Returns a pointer to free with pcap_close() on success.
 */
pcap_t * spcap_new(const char *device);

/* Compile and apply a in-message filter for a handler.
 *
 * Returns -1 on failure, error message is logged;
 * Returns 0 on success;
 */
int spcap_macfilter(pcap_t *pcap, const uint8_t *macaddr, size_t addrlen);

#endif
