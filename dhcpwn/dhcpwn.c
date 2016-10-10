#include "logging.h"
#include "config.h"
#include "rogue.h"

#include <stdlib.h>

#define DHCPWN_SETUP
#include "const.h"
#undef DHCPWN_SETUP

static int setopt(int argc, char **argv);
static int init();

int main(int argc, char **argv)
{
    int status = EXIT_FAILURE;
    rogue_t rogue = NULL;

    log_setup(stderr, LOG_DEBUG);
    log_info("This is %s version %s\n", PACKAGE, VERSION);

    if (setopt(argc, argv) == -1) goto exit;
    if (init() == -1) goto exit;

    rogue = rogue_new_ethrnd();
exit:
    rogue_del(rogue);
    exit(status);;
}

static int setopt(int argc, char **argv)
{
    if (argc < 2) {
        log_error("Usage: %s <device> [options]", argv[0]);
        return -1;
    }

    DHCPWN_Interface = argv[1];

    return 0;
}

#include <time.h>

static int init()
{
    srand(DHCPWN_RandomSeed == 0 ? time(NULL) : DHCPWN_RandomSeed);
    return 0;
}

