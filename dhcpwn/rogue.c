#include "rogue.h"
#include "util.h"
#include "simplecap.h"
#include "const.h"
#include "logging.h"
#include "repr.h"

#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

struct rogue {
    struct {
        uint8_t *macaddr;
        size_t maclen;
    } conf;

    struct {
        pcap_t *cap;
        pthread_t thread;
    } sniffer;

    char *tostr;
};

static void sniffer_teardown(rogue_t);
static int sniffer_setup(rogue_t);
static void * sniffer_thread(void *args);
static void sniffer_loop(u_char *arg, const struct pcap_pkthdr *hdr,
                         const u_char *bytes);

rogue_t rogue_new_ethrnd()
{
    return rogue_new(NULL, 6 /* Ethernet mac len */);
}

rogue_t rogue_new(const uint8_t *macaddr, size_t maclen)
{
    rogue_t out = malloc(sizeof(struct rogue));
    if (out == NULL) goto fail;

    memset((void *)out, 0, sizeof(struct rogue));
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
    free(r->tostr);
    free(r->conf.macaddr);
    free(r);
}

const char *rogue_tostr(rogue_t r)
{
    if (r->tostr == NULL) {
        const char *prefix = "rogue(";
        const char *suffix = ")";
        r->tostr = repr_bytes(r->conf.macaddr, r->conf.maclen,
            ":", prefix, suffix
        );
    }
    return r->tostr;
}

static int sniffer_setup(rogue_t r)
{
    int result = -1;
    char *f1 = NULL;
    char *f2 = NULL;
    char *f3 = NULL;

    r->sniffer.cap = spcap_new(DHCPWN_Interface);
    if (r->sniffer.cap == NULL) {
        goto exit;
    }
    
    f1 = spcap_mkfilter_ether_dst(r->conf.macaddr, r->conf.maclen);
    if (f1 == NULL) {
        goto exit;
    }

    f2 = spcap_mkfilter_proto_dst(SPCAP_PROTO_UDP, DHCPWN_InboundPort);
    if (f2 == NULL) {
        goto exit;
    }

    f3 = spcap_mkfilter_and(f1, f2);
    if (f3 == NULL) {
        goto exit;
    }

    if (spcap_setfilter(r->sniffer.cap, f3) == -1) {
        goto exit;
    }

    pthread_attr_t attr;
    if (pthread_attr_init(&attr) != 0) {
        goto exit;
    }

    result = pthread_create(
        &r->sniffer.thread,
        &attr,
        sniffer_thread,
        (void *)r
    );

    if (result < 0) {
        log_error("Creating thread for %s: %s",
            rogue_tostr(r),
            strerror(result)
        );
    }

    if (pthread_attr_destroy(&attr) != 0) {
        result = -1;
    }

  exit:
    free(f1);
    free(f2);
    free(f3);
    return result;
}

static void sniffer_teardown(rogue_t r)
{
    int ret;
    const char *tostr = rogue_tostr(r);

    log_debug("%s: closing pcap", tostr);
    pcap_breakloop(r->sniffer.cap);

    ret = pthread_cancel(r->sniffer.thread);
    if (ret != 0) {
        log_error("%s: thread cancel error, %s", tostr, strerror(ret));
    }

    log_debug("%s: joining thread", tostr);
    ret = pthread_join(r->sniffer.thread, NULL);
    if (ret != 0) {
        log_error("%s; termination error, %s", tostr, strerror(ret));
    }

    pcap_close(r->sniffer.cap);
}

static void sniffer_loop(u_char *arg, const struct pcap_pkthdr *hdr,
                         const u_char *bytes)
{
    rogue_t r = (rogue_t)arg;

    log_debug("%s: received bytes...", rogue_tostr(r));
}

static void * sniffer_thread(void *arg)
{
    rogue_t r = (rogue_t)arg;
    const int forever = -1;
    const char *tostr = rogue_tostr(r);

    log_debug("%s: thread starting loop", tostr);
    int result = pcap_loop(
        r->sniffer.cap,
        forever,
        sniffer_loop,
        (u_char *)arg
    );

    log_cb_t logger;
    const char *reason;

    switch (result) {
        case 0:
            logger = log_info;
            reason = "no more packets";
            break;
        case -1:
            logger = log_error;
            reason = pcap_geterr(r->sniffer.cap);
            break;
        case -2:
            logger = log_info;
            reason = "interrupted via pcap_break_loop";
            break;
        default:
            logger = log_error;
            reason = "unknown reason";
    }
    logger("%s: interrupted, %s (%d)",
        tostr,
        reason,
        result
    );

    return NULL;
}
