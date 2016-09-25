#include "logging.h"
#include "config.h"
#include "simplecap.h"

#include <stdlib.h>

int main(int argc, char **argv)
{
    log_setup(stderr, LOG_DEBUG);
    log_info("This is %s version %s\n", PACKAGE, VERSION);

    if (argc < 2) {
        log_error("Usage: %s <device> [options]", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *device = argv[1];

    pcap_t *h = spcap_new(device);
    if (h != NULL) {
        log_info("Snapshot size: %d", pcap_snapshot(h));
        pcap_close(h);
    }

}
