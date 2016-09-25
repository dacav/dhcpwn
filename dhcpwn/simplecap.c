#include "simplecap.h"
#include "logging.h"

pcap_t * spcap_new(const char *device)
{
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t *handler = pcap_create(device, errbuf);
    if (handler == NULL) {
        log_error("Unable to open pcap handler for device %s: %s",
            device, errbuf
        );
        return NULL;
    }

    pcap_set_promisc(handler, 1);

    int result = pcap_activate(handler);
    const char *error = NULL;
    const char *details = NULL;
    switch (result) {
        case PCAP_WARNING_PROMISC_NOTSUP:
            error = "promisc not supported";
            details = pcap_geterr(handler);
            break;
        case PCAP_ERROR_NO_SUCH_DEVICE:
            error = "no such device";
            details = pcap_geterr(handler);
            break;
        case PCAP_ERROR_PERM_DENIED:
            error = "permission denied";
            details = pcap_geterr(handler);
            break;

        case PCAP_WARNING_TSTAMP_TYPE_NOTSUP:
            error = "timestamp not supported";
            break;
        case PCAP_ERROR_ACTIVATED:
            error = "already activated";
            break;
        case PCAP_ERROR_PROMISC_PERM_DENIED:
            error = "permission denied for promisc mode";
            break;
        case PCAP_ERROR_RFMON_NOTSUP:
            error = "rf monitor not supported";
            break;
        case PCAP_ERROR_IFACE_NOT_UP:
            error = "interface is not up";
            break;

        case PCAP_WARNING:
        case PCAP_ERROR:
            error = pcap_geterr(handler);

        case 0:
            break;

        default:
            error = "UNKNOWN";
            details = "UNKNOWN";
    }

    if (error || details) {
        log_error("Cannot activate pcap on %s: %s",
            device,
            error == NULL ? details : error
        );
        log_debug("  Details: %s", details == NULL ? "none" : details);
        pcap_close(handler);
        return NULL;
    }

    return handler;
}