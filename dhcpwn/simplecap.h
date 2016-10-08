#ifndef _DHCPWN_SPCAP_H
#define _DHCPWN_SPCAP_H

/* This module provides a conveinent way to handle with libpcap.
 * Functions dealing with filters are assuming the strings to be properly
 * null-terminated. Unless otherwise specified, the caller always retains
 * ownership of input and output objects.
 */

#include <pcap.h>
#include <stdint.h>

/* Create a pcap handler, use application specific settings (e.g. promisc mode).
 *
 * Param device: the choosen network device;
 * Returns NULL on error, error message is logged;
 * Returns a pointer to free with pcap_close() on success.
 */
pcap_t * spcap_new(const char *device);

/* Compile and apply a filter for the given handler.
 *
 * Returns -1 on failure, error message is logged;
 * Returns 0 on success;
 */
int spcap_setfilter(pcap_t *pcap, const char *filter);

typedef enum {
    SPCAP_PROTO_TCP,
    SPCAP_PROTO_UDP,
} spcap_proto_t;

/* Define a filter: ether dst <macaddr>
 *
 * Returns the filter on success. It must be freed by the caller.
 * Returns NULL on failure.
 */
char * spcap_mkfilter_ether_dst(const uint8_t *macaddr, size_t addrlen);

/* Define a filter: <proto> dst <port>
 *
 * Returns the filter on success. It must be freed by the caller.
 * Returns NULL on failure.
 */
char * spcap_mkfilter_proto_dst(spcap_proto_t proto, uint16_t port);

/* Define a filter: (<filter1> and <filter2>)
 *
 * Returns the filter on success. It must be freed by the caller.
 * Returns NULL on failure.
 */
char * spcap_mkfilter_and(char *filter1, char *filter2);

#endif
