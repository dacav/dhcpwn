#include "logging.h"
#include "config.h"

int main(int argc, char **argv)
{
    log_setstream(stderr);
    log_info("This is %s version %s\n", PACKAGE, VERSION);
}
