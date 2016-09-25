#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <repr.h>

int main(int argc, char **argv)
{
    const char bytes[] = {0xde, 0xad, 0xbe, 0xef};
    char * r;

    r = repr_bytes(bytes, sizeof(bytes), NULL, NULL, NULL);
    fprintf(stderr, "%s\n", r);
    assert(strcmp(r, "deadbeef") == 0);
    free(r);

    r = repr_bytes(bytes, sizeof(bytes), ":", NULL, NULL);
    fprintf(stderr, "%s\n", r);
    assert(strcmp(r, "de:ad:be:ef") == 0);
    free(r);

    r = repr_bytes(bytes, sizeof(bytes), NULL, "Real ", NULL);
    fprintf(stderr, "%s\n", r);
    assert(strcmp(r, "Real deadbeef") == 0);
    free(r);

    r = repr_bytes(bytes, sizeof(bytes), NULL, NULL, " Indeed");
    fprintf(stderr, "%s\n", r);
    assert(strcmp(r, "deadbeef Indeed") == 0);
    free(r);

    r = repr_bytes(bytes, sizeof(bytes), NULL, "Actual ", " Indeed");
    fprintf(stderr, "%s\n", r);
    assert(strcmp(r, "Actual deadbeef Indeed") == 0);
    free(r);

    return 0;
}
