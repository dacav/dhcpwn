#include "logging.h"
#include "config.h"
#include "simplecap.h"

#include <stdlib.h>

int main(int argc, char **argv)
{
    pcap_t *h = NULL;
    int status = EXIT_FAILURE;
    char *f1 = NULL;
    char *f2 = NULL;
    char *f3 = NULL;

    log_setup(stderr, LOG_DEBUG);
    log_info("This is %s version %s\n", PACKAGE, VERSION);

    if (argc < 2) {
        log_error("Usage: %s <device> [options]", argv[0]);
        goto exit;
    }

    h = spcap_new(argv[1]);
    if (h == NULL) goto exit;

    log_info("Snapshot size: %d", pcap_snapshot(h));

    f1 = spcap_mkfilter_ether_dst((uint8_t *)"\x00\xde\xad\xbe\xef\x00", 6);
    log_info("f1=%s", f1);
    f2 = spcap_mkfilter_proto_dst(SPCAP_PROTO_UDP, 52);
    log_info("f2=%s", f2);
    f3 = spcap_mkfilter_and(f1, f2);
    log_info("f3=%s", f3);
    status = spcap_setfilter(h, f3) == -1 ? EXIT_FAILURE : EXIT_SUCCESS;

exit:
    free(f1);
    free(f2);
    free(f3);
    if (h != NULL) pcap_close(h);
    exit(status);;
}
