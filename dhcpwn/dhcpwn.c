#include "logging.h"
#include "config.h"
#include "simplecap.h"

#include <stdlib.h>

int main(int argc, char **argv)
{
    pcap_t *h = NULL;
    int status = EXIT_FAILURE;

    log_setup(stderr, LOG_DEBUG);
    log_info("This is %s version %s\n", PACKAGE, VERSION);

    if (argc < 2) {
        log_error("Usage: %s <device> [options]", argv[0]);
        goto exit;
    }

    h = spcap_new(argv[1]);
    if (h == NULL) goto exit;

    log_info("Snapshot size: %d", pcap_snapshot(h));
    spcap_macfilter(h, "\x00\xde\xad\xbe\xef\x00", 6);

    status = EXIT_SUCCESS;
exit:
    if (h != NULL) pcap_close(h);
    exit(status);;
}
