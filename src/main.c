#include "logging.h"

int main(int argc, char **argv)
{
    info("Hello world");
    log_setstream(stderr);
    info("Hi there");
}
