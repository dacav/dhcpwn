#include "rogue.h"
#include "util.h"
#include "simplecap.h"
#include "const.h"

#include <stdlib.h>
#include <string.h>

struct rogue {
    struct {
        uint8_t *macaddr;
        size_t maclen;
    } conf;

    struct {
        pcap_t *pcap;
    } sniffer;
};

static void sniffer_teardown(rogue_t);
static int sniffer_setup(rogue_t);

rogue_t rogue_new_ethrnd()
{
    return rogue_new(NULL, 6 /* Ethernet mac len */);
}

rogue_t rogue_new(const uint8_t *macaddr, size_t maclen)
{
    rogue_t out = malloc(sizeof(struct rogue));
    if (out == NULL) goto fail;

    out->conf.macaddr = calloc(maclen, sizeof(uint8_t));
    if (out->conf.macaddr == NULL) goto fail;
    if (macaddr != NULL) {
        memcpy(out->conf.macaddr, macaddr, maclen);
    } else {
        random_bytes(out->conf.macaddr, maclen);
    }
    out->conf.maclen = maclen;
    if (sniffer_setup(out) == -1) goto fail;
    return out;

  fail:
    rogue_del(out);
    return NULL;
}

void rogue_del(rogue_t r)
{
    if (r == NULL) return;
    sniffer_teardown(r);
    free(r->conf.macaddr);
    free(r);
}

static int sniffer_setup(rogue_t r)
{
    int result = -1;
    char *f1 = NULL;
    char *f2 = NULL;
    char *f3 = NULL;

    r->sniffer.pcap = spcap_new(DHCPWN_Interface);
    if (r->sniffer.pcap == NULL) goto exit;
    
    f1 = spcap_mkfilter_ether_dst(r->conf.macaddr, r->conf.maclen);
    if (f1 == NULL) goto exit;

    f2 = spcap_mkfilter_proto_dst(SPCAP_PROTO_UDP, DHCPWN_InboundPort);
    if (f2 == NULL) goto exit;

    f3 = spcap_mkfilter_and(f1, f2);
    if (f3 == NULL) goto exit;

    result = spcap_setfilter(r->sniffer.pcap, f3);

  exit:
    free(f1);
    free(f2);
    free(f3);
    return result;
}

static void sniffer_teardown(rogue_t r)
{
    pcap_close(r->sniffer.pcap);
}
